#include <stdbool.h>
#include "pixel.h"

typedef struct {
  unsigned int x, y;
  unsigned short max;
  Pixel **data;
} PPM;

PPM* read_ppm();

void change_pixels_lsb(PPM *img, unsigned int size_bits, bool bits[]);

void hide_msg_ppm(PPM *img, const char *msg);
