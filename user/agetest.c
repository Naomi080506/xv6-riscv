#include "kernel/types.h"
#include "user/user.h"

// Add test for aging: starts 3 processes with priorities 1, 5 and 10
// and prints the response time and turnaround time of each one
int
main(int argc, char *argv[])
{
  int prios[] = {1, 5, 10};
  int m = 100; // amount of work for each process (millions of loops)
  if (argc > 1)
    m = atoi(argv[1]);

  setpriority(20); // parent has the highest priority so it can start all the children first
  for (int i = 0; i < 3; i++) {
    int start = uptime();  // time the process was created
    setpriority(prios[i]); // child inherits this priority
    int pid = fork();
    if (pid == 0) {
      int first = uptime(); // first time the child gets the CPU
      volatile uint64 x = 0;
      for (uint64 j = 0; j < (uint64)m * 1000000; j++)
        x += j;               // do some work
      int end = uptime();     // time the child finished
      printf("priority %d: response %d ticks, turnaround %d ticks\n",
             prios[i], first - start, end - start);
      exit(0);
    }
    setpriority(20); // parent goes back to the highest priority
  }
  for (int i = 0; i < 3; i++)
    wait(0);
  exit(0);
}