#ifndef COORD_H
#define COORD_H
typedef struct cd{
	short x;
	short y;
}coord;

coord minus(coord a,coord b);

coord devide(coord a,short scalar);

coord multiply(coord a,short scalar);
#endif
