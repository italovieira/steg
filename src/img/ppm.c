#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

PPM* read_ppm(const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  PPM *img = NULL;

  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
    exit(EXIT_FAILURE);
  }

  img = malloc(sizeof (PPM));

  // Get format type. E.x.: P6
  char type[3];
  fgets(type, sizeof type, fp);
  printf("%s\n", type);

  // Get the width, height and the max value of a pixel
  fscanf(fp, "%u %u %hu", &img->x, &img->y, &img->max);
  printf("%u %u\n%hu\n", img->x, img->y, img->max);

  // Allocate img data
  img->data = malloc(img->y * sizeof (Pixel *));
  for (unsigned int i = 0; i < img->y; i++) {
    img->data[i] = malloc(img->x * sizeof (Pixel));
  }

  // Get the pixels
  for (unsigned int i = 0; i < img->y; i++) {
    fread(img->data[i], sizeof (Pixel), img->x, fp);
    if (ferror(fp)) {
      fprintf(stderr, "steg: error occured while reading file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);
  return img;
}

void write_ppm(PPM *img, const char *filename)
{
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "P6\n%u %u\n%hu", img->x, img->y, img->max);

  // Write the pixels
  for (unsigned int i = 0; i < img->y; i++) {
    unsigned int count = fwrite(img->data[i], sizeof (Pixel), img->x, fp);
    if (count != img->x) {
      fprintf(stderr, "steg: error occured while writing file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);
}
