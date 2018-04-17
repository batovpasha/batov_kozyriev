#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

int TOP_NUMBER = 10; // top 10 of countries

void sorting(int *country_points, int *index, int n) {
  for (int i = 1; i < n; i++) {
    while (country_points[i] > country_points[i - 1] && i > 0) {
      swap(country_points[i], country_points[i - 1]);
      swap(index[i], index[i - 1]);
      i--;
    }
  }
}

void make_top(int *rating_points, string *countries, int n) {
  for (int i = 1; i < n; i++) {
    while (rating_points[i] > rating_points[i - 1] && i > 0) {
      swap(rating_points[i], rating_points[i - 1]);
      swap(countries[i], countries[i - 1]);
      i--;
    }
  }
}

int main() {
  FILE *file = fopen("./text/eurovision.csv", "r");
  int n = 0;
  int size = 10;
  int count = 0;
  char **data = new char*[10];
  while (!feof(file)) {
    if ((count % 10) == 0) {
      char **extend_arr = new char*[size + 10];
      for (int i = 0; i < size; i++) extend_arr[i] = data[i];
      data = extend_arr;
      size += 10;
      count++;
      continue;
    }
    data[n] = new char[200];
    fgets(data[n], 200, file);
    n++;
    count++;
  }
  n--; // must dont count last iteration
  string all_countries[n];
  int points[n][n], transposed[n][n], index_array[n][n];
  int rating_points[n] = {};
  for (int i = 0; i < n; i++) {
    char *pointer = strtok(data[i], ","); // pointer on current point
    int counter = 0;
    while (pointer != nullptr) {
      if (counter == 0) { // push first element to array of countries
        all_countries[i] = pointer;
        pointer = strtok(nullptr, ",");
        counter++;
        continue;
      };
      points[i][counter - 1] = atoi(pointer);
      pointer = strtok(nullptr, ",");
      counter++;
    }
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) index_array[i][j] = j;
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) transposed[j][i] = points[i][j];
  }
  for (int j = 0; j < n; j++) sorting(&transposed[j][0], &index_array[j][0], n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < TOP_NUMBER; j++) {
      if (j == 0) rating_points[index_array[i][j]] += 12;
      if (j == 1) rating_points[index_array[i][j]] += 10;
      if (j > 1) rating_points[index_array[i][j]] += 10 - j;
    }
  }
  make_top(rating_points, &all_countries[0], n);
  fclose(file);
  FILE *output_file = fopen("result.csv", "w");// writing data to output file
  for (int i = 0; i < TOP_NUMBER; i++) {
    fprintf(output_file, "%s,%d\n", all_countries[i].c_str(), rating_points[i]);
  }
  fclose(output_file);
}
