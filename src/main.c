#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
//#include <unistd.h>
//#include <ctype.h>
#include "img/ppm.h"
//#include "img/bpm.c"

const char *get_msg_content(const char *filename)
{
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  unsigned int img_size = ftell(fp);
  rewind(fp);
  char *msg = malloc(img_size * sizeof *msg);

  fread(msg, 1, img_size, fp);

  return msg;
}

int main(int argc, char **argv)
{
  enum {
    NONE,
    ENCODER,
    DECODER
  } mode = NONE;

  char *fmt = NULL, *in = NULL, *out = NULL;
  int c;

  while ((c = getopt(argc, argv, "edf:i:o:h")) != -1) {
    switch (c) {
      case 'h': // Help
        // Print help
        break;
      case 'e': // Help
        mode = ENCODER;
        break;
      case 'd':
        mode = DECODER;
        break;
      case 'f': // Format
        fmt = optarg;
        break;
      case 'i': // Input file
        in = optarg;
        break;
      case 'o': // Output file
        out = optarg;
        break;
      default:
        return EXIT_FAILURE;
    }
  }

  if (argc == 1) {
    fprintf(stderr, "steg: expected arguments.\nTry 'steg -h' for more information.\n");
    return EXIT_FAILURE;
  }

  if (mode == NONE) {
    fprintf(stderr, "steg: missing '-d' or '-e' operand.\n");
    return EXIT_FAILURE;
  }

  if (mode == ENCODER && in == NULL) {
    fprintf(stderr, "steg: missing '-i' operand.\n");
    return EXIT_FAILURE;
  }

  if (mode == DECODER && out == NULL) {
    fprintf(stderr, "steg: missing '-o' operand.\n");
    return EXIT_FAILURE;
  }

  if (fmt == NULL) {
    fprintf(stderr, "steg: missing '-f' operand.\n");
    return EXIT_FAILURE;
  }

  if (optind >= argc) {
    fprintf(stderr, "steg: expected image file.\nTry 'steg -h' for more information.\n");
    return EXIT_FAILURE;
  }

  const char *img_file = argv[optind];

  if (strncmp(fmt, "ppm", 3) == 0) {
    if (mode == ENCODER) {
      PPM *img = read_ppm(img_file);
      const char *msg = get_msg_content(in);
      hide_msg(img->x, img->y, img->data, msg);
      write_ppm(img, img_file);
    } else if (mode == DECODER) {
      PPM *img = read_ppm(img_file);
      get_msg(img->x, img->y, img->data, out);
    }
  } else if (strncmp(fmt, "bmp", 3) == 0) {
    //if (mode == ENCODER) {
    //  BMP *img = read_bmp(img_file);
    //  write_bmp(img, img_file);
    //} else if (mode == DECODER) {
    //}
  } else {
    fprintf(stderr, "Invalid format.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
