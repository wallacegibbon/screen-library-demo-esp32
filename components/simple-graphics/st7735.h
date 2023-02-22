#ifndef __ST7735_H
#define __ST7735_H

#include "painter.h"
#include "common.h"
#include "driver/spi_master.h"
#include <stdint.h>

struct ST7735_Screen {
	struct PainterInterface painter_interface;
	struct Point size;

	/// GPIOs (soft SPI) for controlling ST7735
	uint8_t mosi_pin;
	uint8_t sclk_pin;
	uint8_t cs_pin;
	uint8_t rst_pin;
	uint8_t dc_pin;
};

void ST7735_Screen_initialize(
	struct ST7735_Screen *self,
	uint8_t mosi_pin,
	uint8_t sclk_pin,
	uint8_t cs_pin,
	uint8_t rst_pin,
	uint8_t dc_pin
);

#endif

