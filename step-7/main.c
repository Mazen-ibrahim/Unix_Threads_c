#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>




pthread_mutex_t mutex;

void* routine(void *arg)
{
    if ( pthread_mutex_trylock(&mutex) == 0 )
    {
        printf("Get lock \n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("Failed to Get lock\n");
    }


}



int main()
{   
  
    pthread_t th[4];
    pthread_mutex_init(&mutex,NULL);

    for( int i = 0 ; i<4 ; i++)
    {   
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0)
        {
            perror("Failed to Create Thread\n");
        }
    }
   

    for( int i = 0 ; i<4 ; i++)
    {   

        if(pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join Thread\n");
        }

    }

    pthread_attr_destroy(&mutex);

  

    return 0;
}