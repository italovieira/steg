#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

PPM* read()
{
  // Later use getopt for this
  FILE *fp = fopen("../../.img/imd.ppm", "rb");
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
