#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

struct stack {
  int top;
  void *items[256];
};

void stack_init(struct stack *stack);
bool stack_is_full(struct stack *stack);
bool stack_is_empty(struct stack *stack);
void push(struct stack *stack, void *item);
void pop(struct stack *stack);
void *stack_peek(struct stack *stack);

#endif
