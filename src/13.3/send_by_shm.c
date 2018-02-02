#include <stdio.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/sem.h>
#include <stdlib.h>
#include <string.h> 

int main (int argc, char *argv[]) 
{
  int id;
  char *adr;
  union semun inival;
  struct sembuf semlock;
  struct shmid_ds buf;
  if (argc !=2)
  {
    fprintf(stderr, "Usage: send-by-shm <Shared memory ID>");
    exit (EXIT_FAILURE);
  }

  id=atoi(argv[1]);

  int sid = semget(id, 1,IPC_CREAT | 0700);
  inival.val = 1;
  semctl (sid, 0, SETVAL, inival);
  semlock.sem_num=0;
  semlock.sem_flg=0;

  if((int) (adr = (char *)shmat (id, (void *) 0, 0)) == -1) {
    perror("shmat");
    exit(EXIT_FAILURE);
  } else {
    while(1) {
      if (semctl(sid, 0, GETVAL) == 1) {
        // lock: semaphoreが一個の前提の実装
        semlock.sem_op=-1;
        semop(sid, &semlock, 1);
        printf("Input any string> ");
        fgets(adr, 512, stdin);
        adr[strlen(adr)-1] = '\0';
        if(strcmp (adr, "quit") == 0) {
          break;
        }
      }
    }
    if (shmdt (adr) == -1) {
      perror("shmdt");
      exit (EXIT_FAILURE); 
    }
  }
} 
