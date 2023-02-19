#include "painter.h"
#include "point_iterator.h"
#include <stddef.h>
#include <assert.h>

void Painter_fill_fallback(
	struct Painter *self, struct Point p1, struct Point p2, int color
);

void Painter_clear_fallback(struct Painter *self, int color);

void Painter_draw_point(struct Painter *self, struct Point p, int color) {
	PainterDrawPoint draw_point;

	draw_point = ((struct PainterInterface *) self->screen)->draw_point;
	assert(draw_point != NULL);

	draw_point(self->screen, p, color);
}

void Painter_size(struct Painter *self, struct Point *p) {
	PainterSize size;

	size = ((struct PainterInterface *) self->screen)->size;
	assert(size != NULL);

	size(self->screen, p);
}

void Painter_fill(
	struct Painter *self, struct Point p1, struct Point p2, int color
) {
	PainterFill fill;

	fill = ((struct PainterInterface *) self->screen)->fill;
	if (fill)
		fill(self->screen, p1, p2, color);
	else
		Painter_fill_fallback(self, p1, p2, color);
}

void Painter_clear(struct Painter *self, int color) {
	PainterClear clear;

	clear = ((struct PainterInterface *) self->screen)->clear;
	if (clear)
		clear(self->screen, color);
	else
		Painter_clear_fallback(self, color);
}

void Painter_flush(struct Painter *self) {
	PainterFlush flush;

	flush = ((struct PainterInterface *) self->screen)->flush;
	if (flush)
		flush(self->screen);
}

void Painter_fill_fallback(
	struct Painter *self, struct Point p1, struct Point p2, int color
) {
	struct RectPointIterator point_iterator;
	struct Point p;

	RectPointIterator_initialize(&point_iterator, p1, p2);
	RectPointIterator_describe(&point_iterator);

	while (RectPointIterator_next(&point_iterator, &p))
		Painter_draw_point(self, p, color);
}

void Painter_clear_fallback(struct Painter *self, int color) {
	struct Point p1;
	struct Point p2;

	Point_initialize(&p1, 0, 0);
	Painter_size(self, &p2);
	Painter_fill_fallback(self, p1, p2, color);
}

void Painter_draw_line(
	struct Painter *self, struct Point p1, struct Point p2, int color
) {
	struct LinePointIterator point_iterator;
	struct Point p;

	LinePointIterator_initialize(&point_iterator, p1, p2);

	while (LinePointIterator_next(&point_iterator, &p))
		Painter_draw_point(self, p, color);
}

void Painter_draw_rectangle(
	struct Painter *self, struct Point p1, struct Point p2, int color
) {
	struct Point tmp;

	Point_initialize(&tmp, p2.x, p1.y);
	Painter_draw_line(self, p1, tmp, color);
	Painter_draw_line(self, tmp, p2, color);

	Point_initialize(&tmp, p1.x, p2.y);
	Painter_draw_line(self, p2, tmp, color);
	Painter_draw_line(self, tmp, p1, color);
}

void Painter_draw_cross_points(
	struct Painter *self, struct Point p, int a, int b, int color
) {
	struct Point p1;

	Point_initialize(&p1, p.x - a, p.y + b);
	Painter_draw_point(self, p1, color);

	Point_initialize(&p1, p.x + a, p.y - b);
	Painter_draw_point(self, p1, color);

	Point_initialize(&p1, p.x - a, p.y - b);
	Painter_draw_point(self, p1, color);

	Point_initialize(&p1, p.x + a, p.y + b);
	Painter_draw_point(self, p1, color);
}

void Painter_draw_circle(
	struct Painter *self, struct Point p, int r, int color
) {
	int px = r;
	int py = 0;
	int r_square = r * r;

	while (py <= px) {
		Painter_draw_cross_points(self, p, py, px, color);
		Painter_draw_cross_points(self, p, px, py, color);
		py++;
		if ((py * py + px * px) > r_square)
			px--;
	}
}

