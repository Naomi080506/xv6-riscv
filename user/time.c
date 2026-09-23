#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

// time: runs a command and reports its elapsed (wallclock) time,
// the CPU time it used, and the percentage of the CPU it had.
// Usage: time <command> [args...]

int
main(int argc, char **argv)
{
  // Need at least one argument: the command to time
  if(argc < 2){
    fprintf(2, "usage: time <command> [args...]\n");
    exit(1);
  }

  // Record the clock ticks before starting the command
  int start = uptime();

  // Create a child process to run the command
  int pid = fork();

  if(pid < 0){
    // fork failed
    fprintf(2, "time: fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // Child: replace this program with the command.
    // argv+1 is the null-terminated list of its arguments.
    exec(argv[1], argv+1);

    // exec only returns if it failed
    fprintf(2, "time: exec %s failed\n", argv[1]);
    exit(1);
  }

  // Parent: wait for the child to finish, and get its
  // resource usage (cputime) from the kernel via wait2()
  int status;
  struct rusage ru;
  wait2(&status, &ru);

  // Record the clock ticks after the command finished
  int end = uptime();
  int elapsed = end - start;

  // CPU = share of the elapsed time the child was running.
  // Avoid dividing by zero if the command finished instantly.
  int percent = 0;
  if(elapsed > 0)
    percent = (ru.cputime * 100) / elapsed;

  printf("elapsed time: %d ticks, cpu time: %d ticks, %d%% CPU\n",
         elapsed, ru.cputime, percent);
  exit(0);
}