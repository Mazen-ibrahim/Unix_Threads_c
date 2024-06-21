#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_barrier_t barrier;

void* routine(void *arg)
{
   printf("Waiting For Barrier......\n");
   pthread_barrier_wait(&barrier);
   printf("We Passed The Barrier\n");

}



int main()
{   
    pthread_t th[3];
    pthread_barrier_init(&barrier,NULL,3);
    for(int i = 0 ;i <3; i++)
    {
      if(pthread_create(&th[i],NULL,&routine,NULL) != 0 )
       {
         perror("Failed to Create Thread");
       }

    }
    for( int i = 0 ;i<3; i++)
    {
        if(pthread_join(th[i],NULL) != 0)
        {
            perror("Failed to Join Thread");
        }
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}