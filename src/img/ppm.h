#include <stdbool.h>
#include "pixel.h"

typedef struct {
  unsigned int x, y;
  unsigned short max;
  Pixel **data;
} PPM;

PPM* read_ppm(const char *filename);

void write_ppm(PPM *img, const char *filename);
