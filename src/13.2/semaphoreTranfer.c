#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main() {
  int aAddress = shmget (IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);
  int bAddress = shmget (IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);
  int *a = (int *) shmat (aAddress, (void *) 0, 0);
  int *b = (int *) shmat (bAddress, (void *) 0, 0);
  union semun inival;
  struct sembuf semlock;
  struct shmid_ds buf;
  int sid = semget (aAddress, 1,IPC_CREAT | 0700);
  inival.val = 1;
  semctl (sid, 0, SETVAL, inival);
  semlock.sem_num=0;
  semlock.sem_flg=0;

  if (aAddress == -1 || bAddress == -1) {
    printf("shared memory error\n");
    return -1;
  }

  if (sid == -1) {
    printf("semaphore error\n");
    return -1;
  }

  printf("A Address: %d\n", aAddress);
  printf("B Address: %d\n", bAddress);
  sleep(5);

  *a = 100;
  *b = 0;

  while(1) {
    // lock
    semlock.sem_op=-1;
    if (semop (sid, &semlock, 1) >= 0) {
      printf("(a, b) = (%d, %d)\n", *a, *b);
      *a = *a - 1;
      sleep(1);
      *b = *b + 1;
      sleep(1);
    }

    // unlock
    semlock.sem_op=1;
    semop(sid, &semlock, 1);

    if (*a == 0 && *b == 100) {
      printf("complete!");
		  shmdt(a);
		  shmdt(b);
      break;
    }
  }
}
