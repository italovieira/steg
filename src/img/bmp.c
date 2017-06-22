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
  Header header;
  fread(&header, 1, sizeof header, fp);
  if (ferror(fp)) {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  // Read header info
  HeaderInfo header_info;
  fread(&header_info, 1, sizeof header_info, fp);
  if (ferror(fp)) {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  // Allocate img data
  Pixel **data = malloc(header_info.y * sizeof *data);
  for (unsigned int i = 0; i < header_info.y; i++) {
    data[i] = malloc(header_info.x * sizeof **data);
  }

  // Get the pixels
  for (unsigned int i = 0; i < header_info.y; i++) {
    fread(data[i], sizeof **data, header_info.x, fp);
    if (ferror(fp)) {
      fprintf(stderr, "steg: error occured while reading file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);

  printf("%c%c ", header.type[0], header.type[1]);
  printf("%u ", header.size);
  printf("%u ", header.offset);
  printf("\n");

  printf("%d ", header_info.x);
  printf("%d ", header_info.y);
  printf("\n");

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

  // Write header
  if (fwrite(&img->header, 1, sizeof img->header, fp) != sizeof img->header) {
    fprintf(stderr, "steg: error occured while writing file.\n");
    exit(EXIT_FAILURE);
  }

  // Write header_info
  if (fwrite(&img->header_info, 1, sizeof img->header_info, fp) != sizeof img->header_info) {
    fprintf(stderr, "steg: error occured while writing file.\n");
    exit(EXIT_FAILURE);
  }

  // Write the pixels
  for (unsigned int i = 0; i < img->header_info.y; i++) {
    unsigned int count = fwrite(img->data[i], sizeof (Pixel), img->header_info.x, fp);
    if (count != img->header_info.x) {
      fprintf(stderr, "steg: error occured while writing file.\n");
      exit(EXIT_FAILURE);
    }
  }

  fclose(fp);
}
