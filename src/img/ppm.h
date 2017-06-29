#ifndef PPM_H
#define PPM_H

#include <stdbool.h>
#include "pixel.h"

typedef struct {
  unsigned int x, y;
  unsigned short max;
  Pixel **data;
} PPM;

// Função que acessa o arquivo PPM 'filename' e lê suas devidas informações,
// sendo estas mais simples que o 'BMP': 'width' (x) dos pixels, 'height' (y)
// dos pixels e os pixels em si.  Após a leitura sem erros, a função retorna um
// ponteiro para o struct 'PPM' com as informações lidas.
PPM* read_ppm(const char *filename);

// Acessa o struct 'PPM' de nome 'img' e escreve suas informações, no arquivo
// 'filename'. Funciona como um processo inverso a função 'read_ppm'.
void write_ppm(PPM *img, const char *filename);

#endif
