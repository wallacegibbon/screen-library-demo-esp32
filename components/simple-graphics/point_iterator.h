#ifndef __POINT_ITERATOR_H
#define __POINT_ITERATOR_H

#include "common.h"

struct LinePointIterator {
	struct Point destination;
	struct Point cursor;
	struct Point step;
	struct Point delta;
	struct Point acc;
	int distance;
	int count;
};

struct RectPointIterator {
	struct Point p1;
	struct Point p2;
	struct Point cursor;
};

void RectPointIterator_initialize(
	struct RectPointIterator *self,
	struct Point p1,
	struct Point p2
);

int RectPointIterator_next(
	struct RectPointIterator *self,
	struct Point *result
);

void RectPointIterator_describe(struct RectPointIterator *self);

void LinePointIterator_initialize(
	struct LinePointIterator *self,
	struct Point p1,
	struct Point p2
);

int LinePointIterator_next(
	struct LinePointIterator *self,
	struct Point *result
);

#endif

