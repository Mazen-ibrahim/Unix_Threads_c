#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *CallBack(void *arg)
{  
  sleep(1);
  printf("Finsished Execution\n");
}



int main()
{   
  pthread_t th[2];
  pthread_attr_t detachedThread;
  pthread_attr_init(&detachedThread);
  pthread_attr_setdetachstate(&detachedThread,PTHREAD_CREATE_DETACHED);

  int i ;
  for( i = 0 ; i<2 ; i++)
  {
    if( pthread_create(&th[i],&detachedThread,CallBack,NULL) != 0 )
    {
      perror("Failed to Create Thread\n");
    }

  }

  pthread_exit(0);

}