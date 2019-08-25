#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include "ppm.h"
#include "bmp.h"

void help()
{
  printf("Usage:  steg OPTION... FILE\n\n");
  printf("  -h    Display this usage information.\n"
         "  -e    Run in encoder mode. Expects message from standard input.\n"
         "  -d    Run in decoder mode. Write message in standard output.\n");
  printf("\nFILE refers to image file (BMP) to encode or decode and will be overwritten.\n");
  exit(EXIT_SUCCESS);
}

// Retorna mensagem a ser escondida do arquivo 'fp'.  Também checa se a
// quantidade de pixels é suficiente para gravar toda a mensagem, ao passar a
// informação da área dos pixels que é largura x altura (x * y).
const char *get_msg_content(FILE *fp, unsigned long pixels_size)
{
  if (fp == NULL) {
    fprintf(stderr, "steg: cannot access the file containing the message': %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  unsigned long file_size = ftell(fp);
  if (pixels_size * 3 < (file_size + 1) * 8) {
    fprintf(stderr, "steg: insufficient pixels to store secret message.\n");
    exit(EXIT_FAILURE);
  }
  rewind(fp);

  char *msg = malloc((file_size + 1) * sizeof *msg);
  if (msg == NULL) {
    perror("steg");
    exit(EXIT_FAILURE);
  }

  if (fread(msg, 1, file_size, fp) != file_size) {
    fprintf(stderr, "steg 1: error occured while reading the message from input.\n");
    exit(EXIT_FAILURE);
  }

  char eot[2];
  eot[0] = 0x03;
  strncat(msg, eot, 1);

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

  int c;

  while ((c = getopt(argc, argv, "edh")) != -1) {
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

  if (optind >= argc) {
    fprintf(stderr, "steg: expected image file.\n");
    return EXIT_FAILURE;
  }

  const char *img_file = argv[optind];

  BMP *img = read_bmp(img_file);
  if (mode == ENCODER) {
    // Encoder
    const char *msg = get_msg_content(stdin, img->header_info->x * img->header_info->y);
    hide_msg(img->header_info->x, img->header_info->y, img->data, msg);
    write_bmp(img, img_file);
  } else {
    // Decoder
    save_msg(img->header_info->x, img->header_info->y, img->data);
  }

  return EXIT_SUCCESS;
}
