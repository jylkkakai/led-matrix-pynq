/******************************************************************************
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 ******************************************************************************/

/*
 *
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

// Main program for exercise

//****************************************************
// By default, every outputs used in this exercise is 0
//****************************************************
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"
#include "Pixel.h"
#include "platform.h"

void test() {

  int x = 0, y = 0;
  while (1) {
    set_pixel(x, y, 0xFF, 0xFF, 0xFF);
    usleep(100000);
    set_pixel(x, y, 0x0, 0x0, 0x0);

    if (x >= 7) {
      x = 0;
      if (y >= 7) {
        y = 0;
      } else {
        y++;
      }
    } else {
      x++;
    }
  }
}

void test2() {

  int mode = 0;
  uint8_t r = 0, g = 0, b = 0;
  while (1) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        set_pixel(x, y, r, g, b);
      }
    }
    usleep(10000);

    switch (mode) {
    case 0:
      r++;
      g = 0x0;
      b = 0x0;
      if (r == 0xff)
        mode++;
      break;
    case 1:
      r = 0xff;
      g++;
      b = 0x0;
      if (g == 0xff)
        mode++;
      break;
    case 2:
      r--;
      g = 0xff;
      b = 0x0;
      if (r == 0x0)
        mode++;
      break;
    case 3:
      r = 0x0;
      g = 0xff;
      b++;
      g = 0xff;
      if (b == 0xff)
        mode++;
      break;
    case 4:
      r = 0x0;
      g--;
      b = 0xff;
      if (g == 0x0)
        mode++;
      break;
    case 5:
      r++;
      g = 0x0;
      b = 0xff;
      if (r == 0xFF)
        mode++;
      break;
    case 6:
      r = 0xff;
      g++;
      b = 0xff;
      if (g == 0xff)
        mode++;
      break;
    case 7:
      r = 0xff;
      g = 0xff;
      b--;
      if (b == 0x0)
        mode++;
      break;
    case 8:
      r--;
      g = 0xff;
      b = 0x0;
      if (r == 0x0)
        mode++;
      break;
    case 9:
      r = 0x0;
      g--;
      b = 0x0;
      if (g == 0x0)
        mode = 0;
      break;
    }
  }
}

#define ROWS 8
#define COLUMNS 8

void draw_column(int column, uint8_t r, uint8_t g, uint8_t b) {
  for (int y = 0; y < ROWS; y++) {
    set_pixel(column, y, r, g, b);
  }
}

void test3() {

  const int columns = 8;
  uint8_t colors[COLUMNS] = {0 / 3,   31 / 3,  63 / 3,  95 / 3,
                             127 / 3, 159 / 3, 191 / 3, 223 / 3};
  int dirs[COLUMNS] = {1, 1, 1, 1, 1, 1, 1, 1};
  while (1) {

    for (int i = 0; i < COLUMNS; i++) {
      draw_column(i, colors[i], colors[i], colors[i]);
      colors[i] += dirs[i];
      if (colors[i] >= 255 / 3)
        dirs[i] = -1;
      else if (colors[i] <= 0)
        dirs[i] = 1;
    }
    usleep(10000);
  }
}

int main() {
  init_platform();

  test3();
  cleanup_platform();
  return 0;
}
