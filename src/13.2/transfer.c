#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int aAddress = shmget (IPC_PRIVATE, sizeof(int), IPC_CREAT|0666); int bAddress = shmget (IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);

  int *a = (int *) shmat (aAddress, (void *) 0, 0);
  int *b = (int *) shmat (bAddress, (void *) 0, 0);

  if (aAddress == -1 || bAddress == -1) {
    printf("shared memory error");
    return -1;
  }

  printf("A Address: %d\n", aAddress);
  printf("B Address: %d\n", bAddress);
  sleep(5);

  *a = 100;
  *b = 0;

  while(1) {
    printf("(a, b) = (%d, %d)\n", *a, *b);

    *a = *a - 1;
    sleep(1);
    
    *b = *b + 1;
    sleep(1);

    if (*a == 0 && *b == 100) {
		  shmdt(a);
		  shmdt(b);
      break;
    }
  }
}
