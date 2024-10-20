#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <kernel/queue.h>
#include <stdbool.h>

struct semaphore {
  struct queue *queue;
  bool locked;
};

void semaphore_init(struct semaphore *sem);
void semaphore_enqueue(struct semaphore *sem, void *item);
void semaphore_dequeue(struct semaphore *sem);
void *semaphore_queue_peek(struct semaphore *sem);
void semaphore_take(struct semaphore *sem);
void semaphore_rls(struct semaphore *sem);
void semaphore_cycle(struct semaphore *sem);

#endif
