#ifndef __SSD1306_H
#define __SSD1306_H

#include "painter.h"
#include "common.h"
#include "driver/i2c.h"

struct SSD1306_Screen {
	/// implement some interface to work with Painter. (vtable)
	struct PainterInterface painter_interface;

	struct Point size;

	/// just to hold some value since we don't have closure in C.
	int clear_color;

	/// only the I2C interface is supported.
	i2c_cmd_handle_t cmd_handle;
	i2c_port_t i2c_num;

	/// I2C address.
	uint8_t address;

	/// flag to set SSD1306 upside down.
	uint8_t direction;

	uint8_t auto_flush;

	/// the 128x32 mode.
	uint8_t half_mode;

	uint8_t buffer[128][8];
};

void SSD1306_Screen_initialize(
	struct SSD1306_Screen *self, int address, i2c_port_t i2c_num
);

void SSD1306_Screen_initialize(
	struct SSD1306_Screen *self, int address, i2c_port_t i2c_num
);

void SSD1306_Screen_fix_32row(struct SSD1306_Screen *self);

void SSD1306_Screen_flush(struct SSD1306_Screen *self);

void SSD1306_Screen_set_up_down_invert(struct SSD1306_Screen *self);
void SSD1306_Screen_set_brightness(struct SSD1306_Screen *self, uint8_t value);
void SSD1306_Screen_color_reverse(struct SSD1306_Screen *self);

void SSD1306_Screen_display_on(struct SSD1306_Screen *self);
void SSD1306_Screen_display_off(struct SSD1306_Screen *self);

void SSD1306_Screen_describe(struct SSD1306_Screen *self);

#endif

