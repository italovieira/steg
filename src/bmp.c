#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bmp.h"

BMP* read_bmp(const char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    fprintf(stderr, "steg: cannot access '%s': %s\n",
            filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  // Read header
  Header *header = malloc(sizeof *header);
  if (header == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }

  if (fread(&header->type, sizeof header->type, 1, fp) != 1
      || fread(&header->size, sizeof header->size, 1, fp) != 1
      || fread(&header->reserved1, sizeof header->reserved1, 1, fp) != 1
      || fread(&header->reserved2, sizeof header->reserved2, 1, fp) != 1
      || fread(&header->offset, sizeof header->offset, 1, fp) != 1) {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  if (header->type[0] != 'B' || header->type[1] != 'M') {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  // Read header info
  HeaderInfo *header_info = malloc(sizeof *header_info);
  if (header_info == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }

  if (fread(&header_info->size, sizeof header_info->size, 1, fp) != 1
      || fread(&header_info->x, sizeof header_info->x, 1, fp) != 1
      || fread(&header_info->y, sizeof header_info->y, 1, fp) != 1
      || fread(&header_info->planes, sizeof header_info->planes, 1, fp) != 1
      || fread(&header_info->bit_count,
        sizeof header_info->bit_count, 1, fp) != 1
      || fread(&header_info->compression,
        sizeof header_info->compression, 1, fp) != 1
      || fread(&header_info->img_size,
        sizeof header_info->img_size, 1, fp) != 1
      || fread(&header_info->xresolution,
        sizeof header_info->xresolution, 1, fp) != 1
      || fread(&header_info->yresolution,
        sizeof header_info->yresolution, 1, fp) != 1
      || fread(&header_info->colors_used,
        sizeof header_info->colors_used, 1, fp) != 1
      || fread(&header_info->colors_important,
        sizeof header_info->colors_important, 1, fp) != 1) {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  // Allocate img data
  Pixel **data = malloc(header_info->y * sizeof *data);
  if (data == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }
  for (unsigned int i = 0; i < header_info->y; i++) {
    data[i] = malloc(header_info->x * sizeof *data[i]);
    if (data[i] == NULL) {
      perror("steg");
      exit(EXIT_FAILURE);
    }
  }

  // Get the pixels
  for (unsigned int i = 0; i < header_info->y; i++) {
    fread(data[i], sizeof *data[i], header_info->x, fp);
  }

  fclose(fp);

  BMP *img = malloc(sizeof *img);
  if (img == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }
  img->header = header;
  img->header_info = header_info;
  img->data = data;

  return img;
}

void write_bmp(BMP *img, const char *filename)
{
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
    fprintf(stderr, "steg: cannot access '%s': %s\n",
            filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (fwrite(&img->header->type, sizeof img->header->type, 1, fp) != 1
      || fwrite(&img->header->size,
                sizeof img->header->size, 1, fp) != 1
      || fwrite(&img->header->reserved1,
                sizeof img->header->reserved1, 1, fp) != 1
      || fwrite(&img->header->reserved2,
                sizeof img->header->reserved2, 1, fp) != 1
      || fwrite(&img->header->offset, sizeof img->header->offset, 1, fp) != 1
      || fwrite(&img->header_info->size,
                sizeof img->header_info->size, 1, fp) != 1
      || fwrite(&img->header_info->x, sizeof img->header_info->x, 1, fp) != 1
      || fwrite(&img->header_info->y, sizeof img->header_info->y, 1, fp) != 1
      || fwrite(&img->header_info->planes,
                sizeof img->header_info->planes, 1, fp) != 1
      || fwrite(&img->header_info->bit_count,
                sizeof img->header_info->bit_count, 1, fp) != 1
      || fwrite(&img->header_info->compression,
                sizeof img->header_info->compression, 1, fp) != 1
      || fwrite(&img->header_info->img_size,
                sizeof img->header_info->img_size, 1, fp) != 1
      || fwrite(&img->header_info->xresolution,
                sizeof img->header_info->xresolution, 1, fp) != 1
      || fwrite(&img->header_info->yresolution,
                sizeof img->header_info->yresolution, 1, fp) != 1
      || fwrite(&img->header_info->colors_used,
                sizeof img->header_info->colors_used, 1, fp) != 1
      || fwrite(&img->header_info->colors_important,
          sizeof img->header_info->colors_important, 1, fp) != 1) {
    fprintf(stderr, "steg: error occured while writing file.\n");
    exit(EXIT_FAILURE);
  }

  // Write the pixels
  for (unsigned int i = 0; i < img->header_info->y; i++) {
    if (fwrite(img->data[i], sizeof (Pixel),
        img->header_info->x, fp) != img->header_info->x) {
      fprintf(stderr, "steg: error occured while writing file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);
}
