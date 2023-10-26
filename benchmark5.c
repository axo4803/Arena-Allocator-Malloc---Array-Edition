#include "memalloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
int main( int argc, char * argv[] )
{
  
  //benchmark for malloc 
  struct timeval beginTime;
  struct timeval endTime;
  gettimeofday(&beginTime, NULL);
  char *test[1000]; 
  for (int i = 0; i < 1000; i++)
  {
    test[i] = malloc(10000);
  }
  for (int i = 0; i < 1000; i++)
  {
    free(test[i]);
  }
  gettimeofday(&endTime, NULL);
  double duration = ((endTime.tv_sec * 1000000) + endTime.tv_usec) - (( beginTime.tv_sec * 1000000) + beginTime.tv_usec);
  printf("Duration %.2f\n",duration);
  //Record ten runtime results
  //1947 1953 1929 2104 1979 1929 1980 1948 2079 1903
  return 0;
}
