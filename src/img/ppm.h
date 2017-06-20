#include <stdbool.h>

typedef struct {
  unsigned char r, g, b;
} Pixel;

typedef struct {
  unsigned int x, y;
  unsigned short max;
  Pixel **data;
} PPM;

PPM* read();

bool* get_msg_bits(const char *msg, unsigned int msg_len);

void change_bit_lsb(unsigned char *byte, bool bit);

void change_pixels_lsb(PPM *img, unsigned int size_bits, bool bits[]);

void hide_msg(PPM *img, const char *msg);
