// Test ticket scheduling.


#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int pids[3];

void
forktest(void)
{
  int n, pid;
  printf("ticket test\n");
  printf("parent id: %d\n", getpid());

  for(n=1; n<=3; n++)
  {
    pid = fork();
    if(pid < 0)
    {
      printf("fork failed\n");
      exit(1);
    }
    if(pid == 0)
    {
      settickets(n);
      for(;;)
      {
        sleep(0);
      }
    }
    pids[n-1] = pid;
  }
  sleep(1000);
}

void
getresults(void)
{
    int pid;
    pid = fork();
    if(pid < 0)
    {
      printf("fork failed\n");
      exit(1);
    }
    if(pid == 0)
    {
      char *args[] = { "ps", 0};
      exec("ps", args);
    }
    else 
    {
      sleep(10);
      kill(pids[0]);
      kill(pids[1]);
      kill(pids[2]);
    }
}

int
main(void)
{
  forktest();
  getresults();
  exit(0);
}