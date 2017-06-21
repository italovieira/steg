#include <stdio.h>
#include "../src/img/ppm.h"

void print_rgb_ppm(PPM *img)
{
  for (unsigned int i = 0; i < img->x; i++) {
    for (unsigned int j = 0; j < img->x; j++) {
      printf("%d %d %d\n", img->data[i][j].r, img->data[i][j].g, img->data[i][j].b);
    }
  }
}

int main()
{
  PPM *img = read_ppm();
  //hide_msg_ppm(img, "italo");
  print_rgb_ppm(img);

  return 0;
}
