#ifndef STEP_H
#define STEP_H
#include "coord.h"
#include <stdbool.h>
typedef struct step{
	coord start;
	coord end;
	bool promote;
	short capture;
}step;
#endif
