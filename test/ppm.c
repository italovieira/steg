#include <stdio.h>
#include "../src/img/ppm.h"

void print_rgb(PPM *img)
{
  for (unsigned int i = 0; i < img->x; i++) {
    for (unsigned int j = 0; j < img->x; j++) {
      printf("%d %d %d\n", img->data[i][j].r, img->data[i][j].g, img->data[i][j].b);
    }
  }
}

int main()
{
  PPM *img = read();
  //hide_msg(img, "italo");
  print_rgb(img);

  return 0;
}
