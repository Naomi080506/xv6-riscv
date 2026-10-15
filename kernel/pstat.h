#ifndef PSTAT_H
#define PSTAT_H

// Process states (moved here from proc.h so user programs like ps can use it)
enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// pstat.h: resource usage info returned to user programs by wait2()
struct rusage {
  uint cputime;   // CPU ticks the process used
};

// Process info returned by the getprocs() system call
struct pstat {
  int pid;               // Process ID
  enum procstate state;  // Process state
  uint64 size;           // Size of process memory (bytes)
  int ppid;              // Parent process ID
  int priority;        // Add priority of the process
  uint readytime;       // Add the time (ticks) when the process became RUNNABLE
  char name[16];         // Process command name
};

#endif