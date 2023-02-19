#ifndef __ST7735_H
#define __ST7735_H

#include "painter.h"
#include "common.h"
#include <stdint.h>

struct ST7735_Screen {
	struct PainterInterface painter_interface;
	struct Point size;

	/// GPIOs for controlling ST7735
	uint8_t rst_pin;
	uint8_t dc_pin;
};

#endif

