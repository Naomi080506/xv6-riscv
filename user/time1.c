#include "kernel/types.h"
#include "user/user.h"

// time1: runs a command and reports how many clock ticks
// passed (elapsed time) until the command finished.
// Usage: time1 <command> [args...]

int
main(int argc, char **argv)
{
  // Need at least one argument: the command to time
  if(argc < 2){
    fprintf(2, "usage: time1 <command> [args...]\n");
    exit(1);
  }

  // Record the clock ticks before starting the command
  int start = uptime();

  // Create a child process to run the command
  int pid = fork();

  if(pid < 0){
    // fork failed
    fprintf(2, "time1: fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // Child: replace this program with the command.
    // argv[1] is the command name; argv+1 is the
    // null-terminated list of its arguments.
    exec(argv[1], argv+1);

    // exec only returns if it failed
    fprintf(2, "time1: exec %s failed\n", argv[1]);
    exit(1);
  }

  // Parent: wait for the child to finish
  wait(0);

  // Record the clock ticks after the command finished
  int end = uptime();

  printf("elapsed time: %d ticks\n", end - start);
  exit(0);
}