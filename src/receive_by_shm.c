#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 512

int main()
{
	int id;
	char *adr;

	//-rwxr-xr-x
	if ((id = shmget(IPC_PRIVATE, BUFSIZE, IPC_CREAT|0666)) == -1)
	{
		perror ("shmget");
		exit(EXIT_FAILURE);
	}
	printf("Shared memory ID =%d\n", id);

  //
	if ((int)(adr=(char *) shmat(id, (void *) 0, 0)) == -1)
	{
		perror ("shmat");
		shmctl(id, IPC_RMID, NULL);
		exit (EXIT_FAILURE);
	}
	else
	{
		strcpy (adr, "Initial");
		while(1)
		{
			printf("%s\n", adr);
			if (strcmp (adr, "quit") == 0) {
				break;
			}
			sleep(3);
		}
		
		if (shmdt(adr) == -1)
		{
			perror("shmdt");
			shmctl(id, IPC_RMID, NULL);
			exit (EXIT_FAILURE);
		}
	}
	
	if(shmctl(id, IPC_RMID, NULL) == -1)
	{
		perror("chmctl");
		exit(EXIT_FAILURE);
	}
}
