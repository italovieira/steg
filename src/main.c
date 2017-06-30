#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include "img/ppm.h"
#include "img/bmp.h"

void help()
{
  printf("Usage:  steg OPTION... FILE\n\n");
  printf("  -h    Display this usage information.\n"
         "  -e    Run in encoder mode.\n"
         "  -d    Run in decoder mode.\n"
         "  -f    Image format to encode or decode. Accepts 'ppm' or 'bmp'.\n"
         "  -i    Input file containing the secret message. Expects '-e' option.\n"
         "  -o    Output file to store the decoded message. Expects '-d' option.\n");
  printf("\nFILE refers to image file to encode or decode and will be overwritten.\n");
  exit(EXIT_SUCCESS);
}

// Retorna mensagem a ser escondida do arquivo 'filename'.  Também checa se a
// quantidade de pixels é suficiente para gravar toda a mensagem, ao passar a
// informação da área dos pixels que é largura x altura (x * y).
const char *get_msg_content(const char *filename, unsigned long pixels_size)
{
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "steg: cannot access '%s': %s\n", filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  unsigned long img_size = ftell(fp);
  if (pixels_size * 3 < img_size * 8) {
    fprintf(stderr, "steg: insufficient pixels to store secret message.\n");
    exit(EXIT_FAILURE);
  }
  rewind(fp);

  char *msg = malloc(img_size * sizeof *msg);
  if (msg == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }

  if (fread(msg, 1, img_size, fp) != img_size) {
    fprintf(stderr, "steg: error occured while reading file.\n");
    exit(EXIT_FAILURE);
  }

  return msg;
}

// Função principal que lida com os argumentos do comando e chama as respectivas
// instruções a ser realizadas pelo programa.
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
        help();
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
    help();
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
    fprintf(stderr, "steg: expected image file.\n");
    return EXIT_FAILURE;
  }

  const char *img_file = argv[optind];

  if (strncmp(fmt, "ppm", 3) == 0) {
    PPM *img = read_ppm(img_file);
    if (mode == ENCODER) {
    // Encoder
      const char *msg = get_msg_content(in, img->x * img->y);
      hide_msg(img->x, img->y, img->data, msg);
      write_ppm(img, img_file);
    } else {
    // Decoder
      save_msg(img->x, img->y, img->data, out);
    }
  } else if (strncmp(fmt, "bmp", 3) == 0) {
    BMP *img = read_bmp(img_file);
    if (mode == ENCODER) {
      // Encoder
      const char *msg = get_msg_content(in, img->header_info->x * img->header_info->y);
      hide_msg(img->header_info->x, img->header_info->y, img->data, msg);
      write_bmp(img, img_file);
    } else {
      // Decoder
      save_msg(img->header_info->x, img->header_info->y, img->data, out);
    }
  } else {
    fprintf(stderr, "steg: invalid format.\nTry 'ppm' or 'bmp'.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
