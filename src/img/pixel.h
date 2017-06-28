#include <stdbool.h>

typedef struct {
  unsigned char r, g, b;
} Pixel;

bool* get_msg_bits(const char *msg, unsigned int msg_len);

void change_bit_lsb(unsigned char *byte, bool bit);

void change_pixels_lsb(unsigned int x, unsigned int y, Pixel **data, unsigned
                      int size_bits, bool bits[]);

void hide_msg(unsigned int x, unsigned int y, Pixel **data, const char *msg);

const char *get_msg(unsigned int x, unsigned int y, Pixel **data);
