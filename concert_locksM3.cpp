// ENSC 351 Lab 2
// implement 3 locks

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <atomic>

#define NUM_THREADS 1000 //1000 is too heavy on Surface, laptop locks up
#define NUM_PEOPLE  10000

using namespace std;

bool all_threads_are_created = false;
int theDoor = 0;
int now_serving = 0;
atomic<int> next_ticket(0);

void tickeLock_aquire()
{
    int myTicket = next_ticket++;
    while (now_serving != myTicket);
}

void ticketLock_release()
{
    ++now_serving;
}

void* spin3(void* val){
    int threadNum = *(int*)val;
	while(!all_threads_are_created);

	while(theDoor < NUM_PEOPLE)
	{
		tickeLock_aquire();
		if(theDoor < NUM_PEOPLE)
		{	
			theDoor++;
//			cerr<<"Thread "<< threadNum<<" let Person "<<theDoor<<" through the door."<<endl; //each thread should print this once in a serial order
		}
		ticketLock_release();
	}
	pthread_exit(NULL);
}

int main(){
	pthread_t thread_num[NUM_THREADS] = {0}; // array of pthread identifiers
	int args[NUM_THREADS] = {0};

	for (int i=0; i < NUM_THREADS; i++)
	{
		args[i] = i;
		pthread_create(&thread_num[i], NULL, spin3, &args[i]);
	}

	//release all threads simultaneously:
	all_threads_are_created = true;

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_num[i],NULL);

	return 0;
}