#include "memalloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
int main( int argc, char * argv[] )
{
  //benchmark for first_fit
  struct timeval beginTime;
  struct timeval endTime;
  gettimeofday(&beginTime, NULL);
  memalloc_init(1000 * 10000 ,FIRST_FIT);
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

  //Record ten results for first fit 
  //3004 2997 3009 3542 3016 3055 2975 3041 3118 3262
  return 0;
}
