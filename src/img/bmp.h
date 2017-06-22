#include "pixel.h"

typedef struct {
  unsigned char type[2];
  unsigned int size;
  unsigned short reserved1, reserved2;
  unsigned int offset;
} Header;

typedef struct {
  unsigned int size;
  unsigned int x, y;
  unsigned short planes;
  unsigned short bit_count;
  unsigned int compression;
  unsigned int img_size;
  unsigned int xresolution, yresolution;
  unsigned int colors_used;
  unsigned int colors_important;
} HeaderInfo;

typedef struct {
  Header header;
  HeaderInfo header_info;
  Pixel **data;
} BMP;

BMP* read_bmp(const char *filename);
