#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

PPM* read()
{
  // Later use getopt for this
  FILE *fp = fopen("/home/italo/code/steg/.img/imd.ppm", "rb");
  PPM *img = NULL;

  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
    exit(1);
  } else {
    img = malloc(sizeof (PPM));

    // Get format type. E.x.: P6
    char type[3];
    fgets(type, sizeof type, fp);
    printf("%s\n", type);

    // Get the width, height and the max value of a pixel
    fscanf(fp, "%u %u %hu", &img->x, &img->y, &img->max);
    printf("%u %u\n%hu\n", img->x, img->y, img->max);

    // Allocate img data
    img->data = malloc(img->x * sizeof (Pixel *));
    for (unsigned int i = 0; i < img->x; i++) {
      img->data[i] = malloc(img->y * sizeof (Pixel));
    }

    // Get the pixels
    for (unsigned int i = 0; i < img->x; i++) {
      fread(img->data[i], sizeof (Pixel), img->y, fp);
      if (ferror(fp)) {
        fprintf(stderr, "steg: error occured while reading file.\n");
        exit(1);
      }
    }

    fclose(fp);
    return img;
  }
}

bool* get_msg_bits(const char *msg, unsigned int msg_len)
{
  bool *bits = malloc(8 * (msg_len + 1) * sizeof *bits);
  unsigned int bits_index = 0;

  // Get bits sequence of msg and set to array bits
  for (unsigned int i = 0; i < msg_len + 1; i++) {
    for (short int j = 7; j >= 0; j--) {
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

void change_pixels_lsb(PPM *img, unsigned int size_bits, bool bits[])
{
  unsigned int bits_index = 0;

  for (unsigned int i = 0; i < img->x; i++) {
    for (unsigned int j = 0; j < img->y; j++) {
      unsigned char pixels[sizeof (Pixel)];
      memcpy(pixels, &img->data[i][j], sizeof (Pixel));

      for (unsigned short int k = 0; k < sizeof (Pixel)
          && bits_index < size_bits; k++, bits_index++) {
        change_bit_lsb(&pixels[k], bits[bits_index]);
      }

      memcpy(&img->data[i][j], pixels, sizeof (Pixel));
    }
  }
}

void hide_msg(PPM *img, const char *msg)
{
  unsigned int msg_len = strlen(msg), size_bits = (msg_len + 1) * 8;
  bool *bits = get_msg_bits(msg, msg_len);

  change_pixels_lsb(img, size_bits, bits);
}
