#include <kernel/semaphore.h>
#include <stdlib.h>

void semaphore_init(struct semaphore *sem) {
  sem->locked = false;
}

void semaphore_wait(struct semaphore *sem) {
  while (sem->locked);
}

void semaphore_take(struct semaphore *sem) {
  semaphore_wait(sem);

  sem->locked = true;
}

void semaphore_rls(struct semaphore *sem) { sem->locked = false; }
