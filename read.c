#include <stdio.h>

void read()
{
  FILE *fp = fopen(".img/imd.ppm", "r");

  if (fp == NULL) {
    puts("Unable to open file.");
  } else {
    // Code for manipulate file in here
    fclose(fp);
  }
}
