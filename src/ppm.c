#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "ppm.h"

PPM* read_ppm(const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    fprintf(stderr, "steg: cannot access '%s': %s\n",
            filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  PPM *img = malloc(sizeof (PPM));
  if (img == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }

  // Get format type. E.x.: P6
  char type[3];
  fgets(type, sizeof type, fp);
  if (type[0] != 'P' || type[1] != '6') {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  // Get the width, height and the max value of a pixel
  fscanf(fp, "%u %u %hu ", &img->x, &img->y, &img->max);

  // Allocate img data
  img->data = malloc(img->y * sizeof (Pixel *));
  if (img->data == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }
  for (unsigned int i = 0; i < img->y; i++) {
    img->data[i] = malloc(img->x * sizeof (Pixel));
    if (img->data[i] == NULL) {
      perror("steg");
      exit(EXIT_FAILURE);
    }
  }

  // Get the pixels
  for (unsigned int i = 0; i < img->y; i++) {
    if (fread(img->data[i], sizeof (Pixel), img->x, fp) != img->x) {
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
    fprintf(stderr, "cannot access '%s': %s\n", filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "P6\n%u %u\n%hu\n", img->x, img->y, img->max);

  // Write the pixels
  for (unsigned int i = 0; i < img->y; i++) {
    if (fwrite(img->data[i], sizeof (Pixel), img->x, fp) != img->x) {
      fprintf(stderr, "steg: error occured while writing file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);
}
