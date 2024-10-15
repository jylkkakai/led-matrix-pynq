#include "Pixel.h"
#include "stdint.h"

// Set value of one pixel at led matrix
void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {

  *coord = x | y << 8;
  *data = b | g << 8 | r << 16;
}
