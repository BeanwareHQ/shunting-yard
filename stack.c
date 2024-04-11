/* BY: Jumps Are Op. (jumpsareop@gmail.com)
 * LICENSE: GPLv3-or-later
 */

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include "shyard.h"
#include "stack.h"

static StackItem stack[MAXSTACK];
static StackItem *stackindex;

void initstack(void){
	stackindex = (StackItem*)&stack;
}

bool isempty(void){
	return stackindex == (StackItem*)&stack;
}

void push(StackItem i){
	if(stackindex == (StackItem*)&stack+MAXSTACK){
		fputs("Stack overflow\n", stderr);
		exit(1);
	}
	*stackindex++ = i;
}

StackItem pop(void){
	if(stackindex == (StackItem*)&stack){
		fputs("Stack underflow\n", stderr);
		exit(1);
	}
	return *--stackindex;
}

StackItem ctop(void){
	return *(stackindex-1);
}
