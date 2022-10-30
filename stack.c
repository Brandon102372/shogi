#include "stack.h"

bool isEmpty(stack *st){
	return st->top==-1;
} 

void push(stack *st,step data){
	if(st->top >= MAX_STACK){
		printf("stack is full\n");	
	}else{
		st->top++;
		st->content[st->top]=data;
	}
 
} 

step pop(stack *st){
	step data;
	if(isEmpty(st)){
		//printf("stack is empty\n");
	}else{
		data=st->content[st->top];
		st->top--;
		return data; 
	}
}

void print_stack(stack *st){
	int i;
	for(i=0;i<=st->top;i++){
		coord start=st->content[i].start;
		coord end=st->content[i].end;
		bool prom=st->content[i].promote;
		short cap=st->content[i].capture;
		printf("start: %d,%d end: %d,%d promote: %d capture %d\n",start.x,start.y,end.x,end.y,prom,cap);
	}
}
