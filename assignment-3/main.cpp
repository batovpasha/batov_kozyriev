#include <iostream>

#include "bmp.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cout << "Incorrect input, use: ./a.out input_file output_file multiplier\n";
    return 1;
  }

  char *input_filename = argv[1];
  char *output_filename = argv[2];
  int increase_number = atoi(argv[3]); // increasing number size

  FILE *input = fopen(input_filename, "rb");
  FILE *output = fopen(output_filename, "wb");

  BMPHEAD normal_bf;
  fread(&normal_bf, sizeof(BMPHEAD), 1, input);
  int normal_padding = (4 - (normal_bf.width * sizeof(PIXELDATA)) % 4) % 4;

  BMPHEAD increased_bf;
  increased_bf = normal_bf;
  increased_bf.width = normal_bf.width * increase_number;
  increased_bf.depth = normal_bf.depth * increase_number;
  int increase_padding = (4 - (increased_bf.width * sizeof(PIXELDATA)) % 4) % 4;
  increased_bf.biSizeImage = increased_bf.width * increased_bf.depth * 3;
  increased_bf.filesize = sizeof(BMPHEAD)
                          + increased_bf.biSizeImage
                          + (increase_padding * increased_bf.depth);

  fwrite(&increased_bf, sizeof(BMPHEAD), 1, output);

  for (int i = 0; i < normal_bf.depth; i++) {

    for (int j = 0; j < increase_number; j++) {

      for (int k = 0; k < normal_bf.width; k++) {
        PIXELDATA triple;
        fread(&triple, sizeof(PIXELDATA), 1, input);

        for (int n = 0; n < increase_number; n++) {
          fwrite(&triple, sizeof(PIXELDATA), 1, output);
        }
      }

      for (int m = 0; m < increase_padding; m++)
        fputc(0x00, output);

      if (j + 1 < increase_number)
        fseek(input, -normal_bf.width * sizeof(PIXELDATA), SEEK_CUR);
    }
    fseek(input, normal_padding, SEEK_CUR);
  }

  fclose(input);
  fclose(output);
  return 0;
}
