#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>

struct queue {
  void *items[256];
  int head;
  int tail;
};

void queue_init(struct queue *queue);
bool queue_is_empty(struct queue *queue);
bool queue_is_full(struct queue *queue);
void enqueue(struct queue *queue, void *item);
void dequeue(struct queue *queue);
void *queue_peek(struct queue *queue);

#endif
