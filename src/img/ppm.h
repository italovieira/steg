typedef struct {
  unsigned char r, g, b;
} Pixel;

typedef struct {
  unsigned int x, y;
  unsigned short max;
  Pixel *data;
} PPM;
