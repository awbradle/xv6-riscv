#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct pstat p;
  int i = 0;
  int ret = 0;
  ret = getpinfo(&p);
  if (ret != 0)
    printf("Something went wrong\n");
  for(i = 0; i < NPROC; i++)
  {
    if(p.inuse[i])
    {
        printf("pid: %d tickets: %d ticks: %d\n",p.pid[i], p.tickets[i], p.ticks[i]);
    }
  }
  return 0;
  
}