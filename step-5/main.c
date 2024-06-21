#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>



int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 25, 29};


void* routine(void *arg)
{
  int index = *(int*)arg;
  printf("%d ",prime[index]);
  free(arg);

}



int main()
{   

    pthread_t th[10];
    for( int i = 0 ; i<10 ; i++)
    {   
       int *a = malloc(sizeof(int));
       *a = i;

        if(pthread_create(&th[i], NULL, &routine, a) != 0)
        {
            perror("Failed to Create Thread\n");
        }
    }

    for( int i = 0 ; i<10 ; i++)
    {
        if(pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join Thread\n");
        }
    }

  

    return 0;
}