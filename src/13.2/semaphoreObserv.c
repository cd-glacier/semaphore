#include <stdio.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdlib.h>
#include <string.h> 
#include <sys/sem.h>

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("input A Address and B Address on commandline arg\n");
    return -1;
  }

  int aAddress = atoi (argv[1]);
  int bAddress = atoi (argv[2]);
  int *a = (int *) shmat (aAddress, 0, 0);
  int *b = (int *) shmat (bAddress, 0, 0);
  union semun inival;
  struct sembuf semlock;
  struct shmid_ds buf;
  int sid = semget (aAddress, 1,IPC_CREAT | 0700);
  semlock.sem_num=0;
  semlock.sem_flg=0;

  while(1){
    // lock
    semlock.sem_op=-1;
    if (semop (sid, &semlock, 1) >= 0) {
      printf("a + b = %d\n", *a + *b);
      sleep(1);
    }

    // unlock
    semlock.sem_op=1;
    semop(sid, &semlock, 1);
  }
}
