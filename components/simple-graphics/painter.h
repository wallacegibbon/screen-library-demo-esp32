#ifndef __PAINTER_H
#define __PAINTER_H

#include "common.h"

typedef void (*PainterDrawPoint)(void *self, struct Point p, int color);
typedef void (*PainterSize)(void *self, struct Point *p);

typedef void (*PainterClear)(void *self, int color);
typedef void (*PainterFill)(
	void *self, struct Point p1, struct Point p2, int color
);

typedef void (*PainterFlush)(void *self);


/// Screens who implement the Painter interface should put
/// the PainterInterface at the start of the struct.
struct PainterInterface {
	/// methods that have to exist
	PainterDrawPoint draw_point;
	PainterSize size;

	/// methods with default implementation
	PainterClear clear;
	PainterFill fill;

	/// methods that is optional
	PainterFlush flush;
};

struct Painter {
	void *screen;
};

/// Core functionalities
void Painter_draw_point(struct Painter *self, struct Point p, int color);
void Painter_size(struct Painter *self, struct Point *p);

void Painter_fill(
	struct Painter *self, struct Point p1, struct Point p2, int color
);
void Painter_clear(struct Painter *self, int color);
void Painter_flush(struct Painter *self);

/// Draw methods
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

