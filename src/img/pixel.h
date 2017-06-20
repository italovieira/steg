#include <stdbool.h>

typedef struct {
  unsigned char r, g, b;
} Pixel;

bool* get_msg_bits(const char *msg, unsigned int msg_len);

void change_bit_lsb(unsigned char *byte, bool bit);
