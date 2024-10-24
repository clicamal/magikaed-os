#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <kernel/queue.h>
#include <stdbool.h>

struct semaphore {
  bool locked;
};

void semaphore_init(struct semaphore *sem);
void semaphore_wait(struct semaphore *sem);
void semaphore_take(struct semaphore *sem);
void semaphore_rls(struct semaphore *sem);

#endif
