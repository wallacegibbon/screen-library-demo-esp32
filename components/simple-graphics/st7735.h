#ifndef __ST7735_H
#define __ST7735_H

#include "painter.h"
#include "common.h"
#include "driver/spi_master.h"
#include <stdint.h>

struct ST7735_Screen {
	struct PainterInterface painter_interface;
	struct Point size;

	/// SPI and GPIOs for controlling ST7735
	spi_device_handle_t *dev;
	uint8_t cs_pin;
	uint8_t rst_pin;
	uint8_t dc_pin;
};

void ST7735_Screen_initialize(
	struct ST7735_Screen *self,
	spi_device_handle_t *dev,
	uint8_t cs_pin,
	uint8_t rst_pin,
	uint8_t dc_pin
);

#endif

