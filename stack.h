#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#define MAXSTACK 100

typedef enum Op StackItem;

void initstack(void);
bool isempty(void);
void push(StackItem);
StackItem pop(void);
StackItem ctop(void);

#endif /* STACK_H */
