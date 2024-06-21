#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t stove_mutex[4];
int stove_fuel[4] = {100,100,100,100};

void* routine(void *arg)
{
    for(int i = 0 ; i<4 ; i++)
    {
        if(pthread_mutex_trylock(&stove_mutex[i]) == 0)
        {
            int fuel_needed = (rand()%20);
            if(stove_fuel[i] - fuel_needed < 0)
            {
                printf("No More Fuel... go to home :( \n");
            }
            else
            { 
                stove_fuel[i] -= fuel_needed;
                printf("Fuel left is %d\n",stove_fuel[i]);
            }
            usleep(500000);
            pthread_mutex_unlock(&stove_mutex[i]);
            break;


        }
        else
        {   
           if(i == 3)
           {
            printf("No available stove now.... waiting\n");
            usleep(300000);
            i = 0 ;
           }

        }
    }

}



int main()
{   
    srand(time(NULL));
    pthread_t th[10];

    for(int i = 0 ;i<4; i++)
    {
       pthread_mutex_init(&stove_mutex[i],NULL);
    }

    for(int i = 0 ; i <10 ; i++)
    {
      if( pthread_create(&th[i],NULL,&routine,NULL) != 0 ) 
        {
           perror("Failed to create thread");
        }

    }

    for(int i = 0 ; i <10 ; i++)
    {
      if( pthread_join(th[i],NULL) != 0 ) 
        {
           perror("Failed to join thread");
        }

    }
    
    for(int i = 0 ;i<4; i++)
    {
       pthread_mutex_destroy(&stove_mutex[i]);
    }

    return 0;
}