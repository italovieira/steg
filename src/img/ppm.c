#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

void read()
{
  // Later use getopt for this
  FILE *fp = fopen("../../.img/imd.ppm", "rb");

  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
  } else {
    PPM *img = (PPM *) malloc(sizeof (PPM));

    // Get format type. E.x.: P6
    char type[3];
    fgets(type, sizeof type, fp);
    printf("%s\n", type);

    // Get the width, height and the max value of a pixel
    fscanf(fp, "%u %u %hu", &img->x, &img->y, &img->max);
    printf("%u %u\n%hu\n", img->x, img->y, img->max);

    img->data = malloc(img->x * img->y * sizeof (Pixel));

    fread(img->data, 3, img->x * img->y, fp);
    if (ferror(fp)) {
      fprintf(stderr, "steg: error occured while reading file.\n");
    }

    for (int i = 0; i < 4032; i++) {
      for (int j = 0; j < 3024; j++) {
        printf("%d %d %d\n", img->data[i * img->y + j].r, img->data[i * img->y + j].g, img->data[i * img->y + j].b);
      }
    }

    fclose(fp);
    free(img->data);
  }
}

int main()
{
  read();
}
