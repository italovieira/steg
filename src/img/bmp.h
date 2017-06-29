#ifndef BMP_H
#define BMP_H

#include "pixel.h"

typedef struct {
  unsigned char type[2];
  unsigned int size;
  unsigned short reserved1, reserved2;
  unsigned int offset;
} Header;

typedef struct {
  unsigned int size;
  unsigned int x, y;
  unsigned short planes;
  unsigned short bit_count;
  unsigned int compression;
  unsigned int img_size;
  unsigned int xresolution, yresolution;
  unsigned int colors_used;
  unsigned int colors_important;
} HeaderInfo;

typedef struct {
  Header *header;
  HeaderInfo *header_info;
  Pixel **data;
} BMP;

// Função que acessa o arquivo BMP 'filename' e lê suas devidas informações,
// sendo estas o 'header', 'header_info' e os pixels.  Após a leitura sem erros,
// a função retorna um ponteiro para o struct 'BMP' (definido acima).
BMP* read_bmp(const char *filename);

// Acessa o struct 'BMP' de nome 'img' e escreve suas informações, no arquivo
// 'filename'. Funciona como um processo inverso a função 'read_bmp'.
void write_bmp(BMP *img, const char *filename);

#endif
