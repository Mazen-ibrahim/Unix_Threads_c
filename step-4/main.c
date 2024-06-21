#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine()
{
    for(int i = 0 ; i<1000000; i++)
    {  
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{   
    pthread_t th[4];
    
    pthread_mutex_init(&mutex,NULL);
    
    for(int i = 0 ;i<4; i++)
    {
        if( pthread_create(th+i,NULL,routine,NULL) != 0 )
        {   
            perror("Failed to Create Thread");
            return 1;
        }
    }

    for(int i = 0 ;i<4; i++)
    {
        if( pthread_join(th[i],NULL) != 0)
        {
            return 2;
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("Number of Mails: %d \n",mails);

    return 0;
}