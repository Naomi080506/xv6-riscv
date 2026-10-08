// pstat.h: resource usage info returned to user programs by wait2()
struct rusage {
  uint cputime;   // CPU ticks the process used
};