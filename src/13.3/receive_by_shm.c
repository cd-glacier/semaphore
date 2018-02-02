#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 512

int main()
{
  int id;
  char *adr;
  struct sembuf semlock;
  semlock.sem_num=0;

  // get semaphore
  if ((id = shmget(IPC_PRIVATE, BUFSIZE, IPC_CREAT|0666)) == -1)
  {
    perror ("shmget");
    exit(EXIT_FAILURE);
  }
  printf("Shared memory ID = %d\n", id);

  int sid = semget(id, 1,IPC_CREAT | 0700);

  // attach semaphore
  if ((int)(adr=(char *) shmat(id, (void *) 0, 0)) == -1) {
    perror ("shmat");
    shmctl(id, IPC_RMID, NULL);
    exit (EXIT_FAILURE);
  } else {
    strcpy (adr, "Initial");
    while(1) {
      if (strcmp (adr, "quit") == 0) {
        break;
      }
      if (semctl(sid, 0, GETVAL) == 0) {
        printf("%s\n", adr);
        // unlock
        semlock.sem_op=1;
        semop(sid, &semlock, 1);

      }
    }

    // dettach semaphore
    if (shmdt(adr) == -1)
    {
      perror("shmdt");
      shmctl(id, IPC_RMID, NULL);
      exit (EXIT_FAILURE);
    }
  }

  // delete semaphore
  if(shmctl(id, IPC_RMID, NULL) == -1)
  {
    perror("chmctl");
    exit(EXIT_FAILURE);
  }
}
