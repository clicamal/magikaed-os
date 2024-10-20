#include <kernel/queue.h>
#include <kernel/semaphore.h>
#include <stdlib.h>

void semaphore_init(struct semaphore *sem) {
  sem->locked = false;
  queue_init(sem->queue);
}

void semaphore_enqueue(struct semaphore *sem, void *item) {
  enqueue(sem->queue, item);
}

void semaphore_dequeue(struct semaphore *sem) { dequeue(sem->queue); }

void *semaphore_queue_peek(struct semaphore *sem) {
  return queue_peek(sem->queue);
}

void semaphore_take(struct semaphore *sem) { sem->locked = true; }

void semaphore_rls(struct semaphore *sem) { sem->locked = false; }

void semaphore_cycle(struct semaphore *sem) {
  if (!sem->locked) {
    void (*obs_callback)(void) = semaphore_queue_peek(sem);

    if (obs_callback != NULL) {
      semaphore_take(sem);

      obs_callback();

      semaphore_dequeue(sem);

      semaphore_rls(sem);
    }
  }
}
