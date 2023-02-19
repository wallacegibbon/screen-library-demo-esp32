#include "st7735.h"
#include "point_iterator.h"
#include <stddef.h>

static inline void ST7735_Screen_rst_high(struct ST7735_Screen *self) {
}

static inline void ST7735_Screen_rst_low(struct ST7735_Screen *self) {
}

static inline void ST7735_Screen_dc_high(struct ST7735_Screen *self) {
}

static inline void ST7735_Screen_dc_low(struct ST7735_Screen *self) {
}

void ST7735_Screen_write_byte(struct ST7735_Screen *self, uint8_t data) {
}

void ST7735_Screen_write_data(struct ST7735_Screen *self, uint16_t data) {
	ST7735_Screen_write_byte(self, data >> 8);
	ST7735_Screen_write_byte(self, data & 0xFF);
}

void ST7735_Screen_set_address(
	struct ST7735_Screen *self, struct Point p1, struct Point p2
) {
}

void ST7735_Screen_draw_point(
	struct ST7735_Screen *self, struct Point p, int color
) {
	if (p.x >= self->size.x || p.y >= self->size.y)
		return;

	ST7735_Screen_set_address(self, p, p);
	ST7735_Screen_write_data(self, (uint16_t) color);
}

void ST7735_Screen_size(struct ST7735_Screen *self, struct Point *p) {
	Point_initialize(p, self->size.x, self->size.y);
}

/// The default `fill` calls `draw_point`, which will cause many
/// unnecessary `set_address` invocations.
void ST7735_Screen_fill(
	struct ST7735_Screen *self,
	struct Point p1,
	struct Point p2,
	int color
) {
	struct RectPointIterator point_iterator;
	struct Point p;

	RectPointIterator_initialize(&point_iterator, p1, p2);
	ST7735_Screen_set_address(self, p1, p2);

	while (RectPointIterator_next(&point_iterator, &p))
		ST7735_Screen_write_data(self, (uint16_t) color);
}

void ST7735_Screen_initialize(
	struct ST7735_Screen *self
) {
	self->painter_interface.draw_point =
		(PainterDrawPoint) ST7735_Screen_draw_point;

	self->painter_interface.size = (PainterSize) ST7735_Screen_size;

	self->painter_interface.clear = NULL;
	self->painter_interface.fill = (PainterFill) ST7735_Screen_fill;

	self->painter_interface.flush = NULL;

	self->size.x = 160;
	self->size.y = 80;
}

