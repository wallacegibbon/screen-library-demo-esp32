#ifndef __PAINTER_H
#define __PAINTER_H

#include "common.h"

typedef void (*PainterDrawPoint)(void *self, struct Point p, int color);

typedef void (*PainterClear)(
	void *self, struct Point p1, struct Point p2, int color
);

typedef void (*PainterFlush)(void *self);

/// Screens who implement the Painter interface should put
/// the PainterInterface at the start of the struct.
struct PainterInterface {
	PainterDrawPoint draw_point;
	PainterClear clear;
	PainterFlush flush;
};

struct Painter {
	void *screen;
};

void Painter_draw_point(struct Painter *self, struct Point p, int color);

void Painter_clear(
	struct Painter *self, struct Point p1, struct Point p2, int color
);

void Painter_flush(struct Painter *self);

void Painter_draw_line(
	struct Painter *self, struct Point p1, struct Point p2, int color
);

void Painter_draw_rectangle(
	struct Painter *self, struct Point p1, struct Point p2, int color
);

void Painter_draw_circle(
	struct Painter *self, struct Point p, int r, int color
);

#endif

