#ifndef PIXEL_H
#define PIXEL_H

#include <stdbool.h>

typedef struct {
  unsigned char r, g, b;
} Pixel;

// Função apenas de apoio a função 'hide_msg', que pega a string 'msg' e o
// tamanho da mesma, e retorna um array de bits sequenciais que representam a
// mensagem.
bool* get_msg_bits(const char *msg, unsigned int msg_len);

// Função apenas de apoio a função 'changes_pixel_lsb', que altera o bit menos
// significativo de 'byte' para o bit definido em 'bit'.
void change_bit_lsb(unsigned char *byte, bool bit);

// Recebe a largura e altura dos pixels e um ponteiro para os pixels e altera
// cada componente (R, G e B) de cada pixel pelo array de bits, em sequência.
void change_pixels_lsb(unsigned int x, unsigned int y, Pixel **data, unsigned
                      int size_bits, bool bits[]);

// Essa função pega a mensagem 'msg' e a esconde nos bits menos siginificativos
// dos pixels, com largura 'x' e altura 'y', com o apoio da função
// 'changes_bit_lsb'.
void hide_msg(unsigned int x, unsigned int y, Pixel **data, const char *msg);

// Essa função obtém a mensagem secreta escondida em no array de pixels 'data' e
// a grava no arquivo 'filename'.
void save_msg(unsigned int x, unsigned int y, Pixel **data);

#endif
