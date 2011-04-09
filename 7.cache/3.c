#define _GNU_SOURCE 
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>



volatile long long array[1000];



void *counter_0()
{
int i;
for(i=0; i<20;i++)
for(array[0]=0; array[0]<100000000; array[0]++);
pthread_exit(NULL);
}
void *counter_rand()
{
srand(time(NULL));
int id=rand()%1000;
int i,j;
for(i=0; i<20;i++)
{
for(j=0;j<1000;j++)
array[j]=0;
for(array[id]=0; array[id]<100000; array[id]++)
id=rand()%1000;
}
pthread_exit(NULL);
}
int main() 
{
cpu_set_t cpu1, cpu2;
CPU_ZERO(&cpu1);
CPU_SET(0, &cpu1);
CPU_ZERO(&cpu2);
CPU_SET(1, &cpu2);
pthread_t thread1;
pthread_t thread2;



if (pthread_create(&thread1, NULL, counter_0,NULL))
{
printf("create thread 1 error");
return 1;
}
if (pthread_create(&thread2, NULL, counter_rand,NULL))
{
printf("create thread 2 error");
return 2;
}
if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu1))
{
printf("set affinity thread 1 error");
return 3;
}
if (pthread_setaffinity_np(thread2, sizeof(cpu_set_t), &cpu2))
{
printf("set affinity thread 2 error");
return 4;
}
if (pthread_join(thread1, NULL))
{
printf("join thread 1 error");
return 5;
}
if (pthread_join(thread2, NULL))
{
printf("join thread 2 error");
return 6;
}
return 0;
}
