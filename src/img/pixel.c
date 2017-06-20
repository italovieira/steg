#include <stdlib.h>
#include "pixel.h"

bool* get_msg_bits(const char *msg, unsigned int msg_len)
{
  bool *bits = malloc(8 * (msg_len + 1) * sizeof *bits);
  unsigned int bits_index = 0;

  // Get bits sequence of msg and set to array bits
  for (unsigned int i = 0; i < msg_len + 1; i++) {
    for (int j = 7; j >= 0; j--) {
      bits[bits_index] = msg[i] >> j & 0x01;
      bits_index++;
    }
  }
  return bits;
}

// Change the lsb of byte RGB to bit
void change_bit_lsb(unsigned char *byte, bool bit)
{
  *byte = bit ? *byte | 0x01 : *byte & 0xFE;
}
