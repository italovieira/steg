#include <stdio.h>
#include "ppm.h"

void read()
{
  FILE *fp = fopen("../../.img/imd.ppm", "rb");

  if (fp == NULL) {
    perror("steg: cannot open 'FILE'");
  } else {
    char c;
      while ((c = fgetc(fp)) != EOF) {
          putchar(c);
      }
    fclose(fp);
  }
}

int main()
{
  read();
}
