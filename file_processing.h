#ifndef FILE_PROCESSING
#define FILE_PROCESSING
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "step.h"
void write_file(const stack *st,const char *name);
void read_file(stack *record,const char *name);
#endif
