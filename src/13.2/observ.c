#include <stdio.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdlib.h>
#include <string.h> 

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("input A Address and B Address on commandline arg\n");
    return -1;
  }

  int aAddress = atoi (argv[1]);
  int bAddress = atoi (argv[2]);

  int *a = (int *) shmat (aAddress, 0, 0);
  int *b = (int *) shmat (bAddress, 0, 0);

  while(1){
    printf("a + b = %d\n", *a + *b);
    sleep(1);
  }
}
