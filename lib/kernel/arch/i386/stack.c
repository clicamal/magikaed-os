#include <kernel/stack.h>
#include <stdlib.h>

void stack_init(struct stack *stack) { stack->top = -1; }

bool stack_is_full(struct stack *stack) { return stack->top >= 255; }

bool stack_is_empty(struct stack *stack) { return stack->top == -1; }

void push(struct stack *stack, void *item) {
  if (stack_is_full(stack)) return;

  stack->items[++stack->top] = item;
}

void pop(struct stack *stack) {
  if (stack_is_empty(stack)) return;

  stack->top--;
}

void *stack_peek(struct stack *stack) {
  if (stack_is_empty(stack)) return NULL;

  return stack->items[stack->top];
}
