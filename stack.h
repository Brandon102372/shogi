#ifndef STACK_H
#define STACK_H

#define MAX_STACK 10000
#include "coord.h"
#include "step.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
	int top;
	step content[MAX_STACK];
}stack;

bool isEmpty(stack *st);
void push(stack *st,step data); 
step pop(stack *st);
void print_stack(stack *st);
#endif
