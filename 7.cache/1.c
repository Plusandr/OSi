#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile long long array[100];

static void *counter(void *args) 
{
	int id = (int)args;
	for(array[id]=0; array[id]<100000000; array[id]++);
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

	if (pthread_create(&thread1, NULL, counter, (void*)0))
	{
		printf("create thread 1 error");
		return 1;
	}
	if (pthread_create(&thread2, NULL, counter, (void*)1))
	{
		printf("create thread 2 error");
		return 2;
	}
	if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu1))
	{
		printf("set affinity thread 1 error");
		return 3;
	}
	if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu2))
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