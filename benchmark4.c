#include "memalloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
int main( int argc, char * argv[] )
{
  //benchmark for next_fit
  struct timeval beginTime;
  struct timeval endTime;
  gettimeofday(&beginTime, NULL);
  memalloc_init(1000 * 10000 , NEXT_FIT);
  char *test[1000];
  for (int i = 0; i < 1000; i++)
  {
    test[i] = memalloc_alloc(10000);
  }
  
  for (int i = 0; i < 1000; i++)
  {
   if (i % 2)
      memalloc_free(test[i]); 
  }
  memalloc_destroy();

  gettimeofday(&endTime, NULL);
  double duration = ((endTime.tv_sec * 1000000) + endTime.tv_usec) - (( beginTime.tv_sec * 1000000) + beginTime.tv_usec);
  printf("Duration %.2f\n",duration);

  //Record ten results for next fit 
  //1812 2058 1820 2081 1832 1872 1802 1836 2235 1833
  return 0;
}
