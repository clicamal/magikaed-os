#include <kernel/queue.h>
#include <stdlib.h>

void queue_init(struct queue *queue) {
  queue->head = -1;
  queue->tail = 0;
}

bool queue_is_empty(struct queue *queue) { return (queue->head == queue->tail - 1); }

bool queue_is_full(struct queue *queue) { return (queue->tail == 256); }

void enqueue(struct queue *queue, void *item) {
  if (queue_is_full(queue)) return;

  queue->items[queue->tail] = item;
  queue->tail++;
}

void dequeue(struct queue *queue) {
  if (queue_is_empty(queue)) return;

  queue->head++;
}

void *queue_peek(struct queue *queue) {
  if (queue_is_empty(queue)) return (void *) NULL;

  return queue->items[queue->head + 1];
}
