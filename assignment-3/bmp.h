#include <stdint.h>

typedef struct {
  int8_t id[2];            // Завжди дві літери 'B' і 'M'
  int32_t filesize;        // Розмір файла в байтах
  int16_t reserved[2];     // 0, 0
  int32_t headersize;      // 54L для 24-бітних зображень
  int32_t infoSize;        // 40L для 24-бітних зображень
  int32_t width;           // ширина зображення в пікселях
  int32_t depth;           // висота зображення в пікселях
  int16_t biPlanes;        // 1 (для 24-бітних зображень)
  int16_t bits;            // 24 (для 24-бітних зображень)
  int32_t biCompression;   // 0L
  int32_t biSizeImage;     // Можна поставити в 0L для зображень без компрессії (наш варіант)
  int32_t biXPelsPerMeter; // Рекомендована кількість пікселів на метр, можна 0L
  int32_t biYPelsPerMeter; // Те саме, по висоті
  int32_t biClrUsed;       // Для індексованих зображень, можна поставити 0L
  int32_t biClrImportant;  // Те саме
} __attribute__((__packed__))
BMPHEAD;

typedef struct {
  int8_t redComponent;
  int8_t greenComponent;
  int8_t blueComponent;
} __attribute__((__packed__))
PIXELDATA;
