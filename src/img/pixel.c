#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

void change_pixels_lsb(unsigned int x, unsigned int y, Pixel **data, unsigned int size_bits, bool bits[])
{
  unsigned int bits_index = 0;

  for (unsigned int i = 0; i < y; i++) {
    for (unsigned int j = 0; j < x; j++) {
      unsigned char pixels[sizeof (Pixel)];
      memcpy(pixels, &data[i][j], sizeof (Pixel));

      for (unsigned short int k = 0; k < sizeof (Pixel)
          && bits_index < size_bits; k++, bits_index++) {
        change_bit_lsb(&pixels[k], bits[bits_index]);
      }

      memcpy(&data[i][j], pixels, sizeof (Pixel));
    }
  }
}

void hide_msg(unsigned int x, unsigned int y, Pixel **data, const char *msg)
{
  unsigned int msg_len = strlen(msg), size_bits = (msg_len + 1) * 8;
  bool *bits = get_msg_bits(msg, msg_len);

  change_pixels_lsb(x, y, data, size_bits, bits);
}

void get_msg(unsigned int x, unsigned int y, Pixel **data)
{
  char c = 0;
  unsigned int bits_index = 0;

  for (unsigned int i = 0; i < y; i++) {
    for (unsigned int j = 0; j < x; j++) {
      unsigned char pixels[sizeof (Pixel)];
      memcpy(pixels, &data[i][j], sizeof (Pixel));

      for (unsigned short int k = 0; k < sizeof (Pixel); k++, bits_index++) {
        unsigned char bit_position = bits_index % 8;
        bool lsb_bit = pixels[k] & 1; // Bit index, 8 by 8

        c |= lsb_bit << (7 - bit_position);

        if (bit_position == 7) {
          putchar(c);
          // If it's the end of the message, then break out of nested for loops
          if (c == '\0') {
            putchar('\n');
            return;
          }
          c = 0;
        }
      }
    }
  }
}
