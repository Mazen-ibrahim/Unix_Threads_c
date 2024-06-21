#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM  8
int dice_Values[8];
int Status[8] = {0};

pthread_barrier_t barrier_RolledDice;
pthread_barrier_t barrier_Calculated;

void *rollDice(void *arg)
{ 
  int index = *(int*)arg;
  while(1)
  {
    dice_Values[index] = rand() % 6 + 1;
    pthread_barrier_wait(&barrier_RolledDice);
    pthread_barrier_wait(&barrier_Calculated);
    if(Status[index] == 1 )
    {
      printf("(%d Rolled %d) I Won\n",index,dice_Values[index]);
    }

    else
    {
      printf("(%d Rolled %d) I Lost\n",index,dice_Values[index]);
    }
  }
  free(arg);

}



int main()
{   

    srand(time(NULL));
    
    pthread_barrier_init(&barrier_RolledDice,NULL,THREAD_NUM + 1);
    pthread_barrier_init(&barrier_Calculated,NULL,THREAD_NUM + 1);

    pthread_t th[THREAD_NUM];
    for(int i = 0 ;i <THREAD_NUM; i++)
    {  
      int* a = malloc(sizeof(int));
      *a = i;
      if(pthread_create(&th[i],NULL,&rollDice, a) != 0 )
       {
         perror("Failed to Create Thread");
       }

    }
    while(1)
    {
      pthread_barrier_wait(&barrier_RolledDice);
      int max = 0;
      for(int i = 0 ; i<THREAD_NUM; i++)
      {
        if( dice_Values[i] > max )
        {
          max = dice_Values[i]; 
        }
      }

      for(int i = 0 ; i<THREAD_NUM ; i++)
      {
        if( dice_Values[i] == max )
          Status[i] = 1;

        else
          Status[i] = 0;

      }
      printf("===== New Round Started ======\n");
      sleep(1);
      pthread_barrier_wait(&barrier_Calculated);

    }

    for( int i = 0 ;i<THREAD_NUM; i++)
    {
      if(pthread_join(th[i],NULL) != 0)
      {
        perror("Failed to Join Thread");
      }
    }

    pthread_barrier_destroy(&barrier_RolledDice);
    pthread_barrier_destroy(&barrier_Calculated);

    return 0;
}