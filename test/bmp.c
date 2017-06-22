#include <stdio.h>
#include "../src/img/bmp.h"

void print_rgb_bmp(BMP *img)
{
  for (unsigned int i = 0; i < img->header_info.y; i++) {
    for (unsigned int j = 0; j < img->header_info.x; j++) {
      printf("%d %d %d\n", img->data[i][j].r, img->data[i][j].g, img->data[i][j].b);
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    return 1;
  }

  BMP *img = read_bmp(argv[1]);
  //hide_msg_bmp(img, "italo");
  print_rgb_bmp(img);

  return 0;
}
