#include "kernel/types.h"
#include "user/user.h"

// Add test program for getpriority and setpriority
int
main(void)
{
  printf("Starting priority: %d\n", getpriority());

  setpriority(10);
  printf("After setpriority(10): %d\n", getpriority());

  if(setpriority(60) < 0)
    printf("setpriority(60) failed as expected (must be 0-49)\n");
  printf("Priority is still: %d\n", getpriority());

  int pid = fork();
  if(pid == 0){
    printf("Child priority (should be 10, inherited): %d\n", getpriority());
    exit(0);
  }
  wait(0);
  exit(0);
}