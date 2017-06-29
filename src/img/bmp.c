#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

BMP* read_bmp(const char *filename)
{
  FILE *fp = fopen(filename, "rb");

  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
    exit(EXIT_FAILURE);
  }

  // Read header
  Header *header = malloc(sizeof *header);

  fread(&header->type, sizeof header->type, 1, fp);
  fread(&header->size, sizeof header->size, 1, fp);
  fread(&header->reserved1, sizeof header->reserved1, 1, fp);
  fread(&header->reserved2, sizeof header->reserved2, 1, fp);
  fread(&header->offset, sizeof header->offset, 1, fp);

  if (ferror(fp)) {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  // Read header info
  HeaderInfo *header_info = malloc(sizeof *header_info);

  fread(&header_info->size, sizeof header_info->size, 1, fp);
  fread(&header_info->x, sizeof header_info->x, 1, fp);
  fread(&header_info->y, sizeof header_info->y, 1, fp);
  fread(&header_info->planes, sizeof header_info->planes, 1, fp);
  fread(&header_info->bit_count, sizeof header_info->bit_count, 1, fp);
  fread(&header_info->compression, sizeof header_info->compression, 1, fp);
  fread(&header_info->img_size, sizeof header_info->img_size, 1, fp);
  fread(&header_info->xresolution, sizeof header_info->xresolution, 1, fp);
  fread(&header_info->yresolution, sizeof header_info->yresolution, 1, fp);
  fread(&header_info->colors_used, sizeof header_info->colors_used, 1, fp);
  fread(&header_info->colors_important, sizeof header_info->colors_important, 1, fp);

  if (ferror(fp)) {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  // Allocate img data
  Pixel **data = malloc(header_info->y * sizeof *data);
  for (unsigned int i = 0; i < header_info->y; i++) {
    data[i] = malloc(header_info->x * sizeof **data);
  }

  // Get the pixels
  for (unsigned int i = 0; i < header_info->y; i++) {
    fread(data[i], sizeof **data, header_info->x, fp);
    if (ferror(fp)) {
      fprintf(stderr, "steg: error occured while reading file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);

  BMP *img = malloc(sizeof *img);
  img->header = header;
  img->header_info = header_info;
  img->data = data;

  return img;
}

void write_bmp(BMP *img, const char *filename)
{
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
    exit(EXIT_FAILURE);
  }


  fwrite(&img->header->type, sizeof img->header->type, 1, fp);
  fwrite(&img->header->size, sizeof img->header->size, 1, fp);
  fwrite(&img->header->reserved1, sizeof img->header->reserved1, 1, fp);
  fwrite(&img->header->reserved2, sizeof img->header->reserved2, 1, fp);
  fwrite(&img->header->offset, sizeof img->header->offset, 1, fp);

  fwrite(&img->header_info->size, sizeof img->header_info->size, 1, fp);
  fwrite(&img->header_info->x, sizeof img->header_info->x, 1, fp);
  fwrite(&img->header_info->y, sizeof img->header_info->y, 1, fp);
  fwrite(&img->header_info->planes, sizeof img->header_info->planes, 1, fp);
  fwrite(&img->header_info->bit_count, sizeof img->header_info->bit_count, 1, fp);
  fwrite(&img->header_info->compression, sizeof img->header_info->compression, 1, fp);
  fwrite(&img->header_info->img_size, sizeof img->header_info->img_size, 1, fp);
  fwrite(&img->header_info->xresolution, sizeof img->header_info->xresolution, 1, fp);
  fwrite(&img->header_info->yresolution, sizeof img->header_info->yresolution, 1, fp);
  fwrite(&img->header_info->colors_used, sizeof img->header_info->colors_used, 1, fp);
  fwrite(&img->header_info->colors_important, sizeof img->header_info->colors_important, 1, fp);

  // Write the pixels
  for (unsigned int i = 0; i < img->header_info->y; i++) {
    unsigned int count = fwrite(img->data[i], sizeof (Pixel), img->header_info->x, fp);
    if (count != img->header_info->x) {
      fprintf(stderr, "steg: error occured while writing file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);
}
