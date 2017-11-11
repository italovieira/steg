#include <stdio.h>
#include "../src/ppm.h"

void print_rgb_ppm(PPM *img)
{
  for (unsigned int i = 0; i < img->y; i++) {
    for (unsigned int j = 0; j < img->x; j++) {
      printf("%d %d %d\n", img->data[i][j].r, img->data[i][j].g, img->data[i][j].b);
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    return 1;
  }

  PPM *img = read_ppm(argv[1]);
  //hide_msg_ppm(img, "italo");
  print_rgb_ppm(img);

  return 0;
}
