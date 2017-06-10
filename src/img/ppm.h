typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} Pixel;

typedef struct {
  unsigned int width;
  unsigned int height;
  unsigned short max;
  Pixel pixels[1000][1000];
} PPM;
