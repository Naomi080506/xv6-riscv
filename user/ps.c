#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
  char *state;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  uint now = uptime(); // Add get the current time to calculate the age

  printf("pid\tstate\t\tsize\tage\tpriority\tppid\tname\n"); // Add age and priority columns
  for (i=0; i<nprocs; i++) {
    state = states[uproc[i].state];
    uint age = 0;
    if (uproc[i].state == RUNNABLE)
      age = now - uproc[i].readytime; // Add age = current time - readytime, only for RUNNABLE processes
    printf("%d\t%s\t%ld\t%d\t%d\t\t%d\t%s\n", uproc[i].pid, state,
                   uproc[i].size, age, uproc[i].priority, uproc[i].ppid, uproc[i].name); // Fix %l to %ld since size is uint64, and add age and priority
  }
  
  exit(0);
}

