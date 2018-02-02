#include <stdio.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdlib.h>
#include <string.h> 

int main (int argc, char *argv[]) 
{
  int id;
  char *adr;

  if (argc !=2)
  {
    fprintf(stderr, "Usage: send-by-shm <Shared memory ID>");
    exit (EXIT_FAILURE);
  }

  id=atoi(argv[1]);
  if((int) (adr = (char *)shmat (id, (void *) 0, 0)) == -1)
  {
    perror("shmat");
    exit(EXIT_FAILURE);
  }
  else
  {
    while(1)
    {
      printf("Input any string>");
      fgets(adr, 512, stdin);
      adr[strlen(adr)-1] = '\0';
      if(strcmp (adr, "quit") == 0)
        break;
    }
    if (shmdt (adr) == -1)
    {
      perror("shmdt");
      exit (EXIT_FAILURE); 
    }
  } 
}
