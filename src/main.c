#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
//#include <unistd.h>
#include <ctype.h>
#include "img/ppm.h"
//#include "img/bpm.c"

int main(int argc, char **argv)
{
  char *fmt = NULL, *in = NULL, *out = NULL;
  int c;

  while ((c = getopt(argc, argv, "f:i:o:h")) != -1) {
    switch (c) {
      case 'h': // Help
        // Print help
        break;
      case 'f': // Format
        fmt = optarg;
        break;
      case 'i': // Input file
        in = optarg;
        break;
      case 'o': // Output file
        out = optarg;
        break;
      case '?':
        if (optopt == 'f' || optopt == 'i' || optopt == 'o') {
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        } else if (isprint(optopt)) {
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        } else {
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        }
        return 1;
      default:
        abort();
    }
  }

  if (!strncmp(fmt, "ppm", 3)) {
    read_ppm(in);
  } else if (!strncmp(fmt, "bmp", 3)) {
    //read_bmp(in);
  } else {
    fprintf(stderr, "Invalid format.\n");
    return 1;
  }

  return 0;
}
