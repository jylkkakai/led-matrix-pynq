#ifndef PIXEL_H_
#define PIXEL_H_

// #include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xgpiops.h"
// #include "../../led_matrix_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xparameters.h"
// #include "../../led_matrix_bsp/ps7_cortexa9_0/include/xscugic.h"
// #include "../../led_matrix_bsp/ps7_cortexa9_0/include/xttcps.h"
#include "platform.h"

// static uint16_t *coord = (uint16_t *)0x41220000;
// static uint32_t *data = (uint32_t *)0x41210000;
static int *coord = (int *)XPAR_AXI_COORD_BASEADDR;
static int *data = (int *)XPAR_AXI_DATA_BASEADDR;
void setup();
void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
#endif /* PIXEL_H_ */
