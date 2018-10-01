// ENSC 351 Lab 2
// implement 3 locks

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 1000
#define NUM_PEOPLE	10000

using namespace std;

bool all_threads_are_created = false;

int theDoor = 0;
pthread_mutex_t lock;


// method 1: single pthread_lock
// can't find pthread_lock... use pthread_mutex_lock?
//yup, i think that is what he meant

void* spin1(void* val){
	int thread_num = *(int *)val;
	while(!all_threads_are_created);

	while(theDoor < NUM_PEOPLE)
	{
		pthread_mutex_lock(&lock);
		if(theDoor < NUM_PEOPLE)
		{
			theDoor += 1;
			cerr<<"Thread "<<thread_num<<" let person "<<theDoor<<" through the door."<<endl; //each thread should print this once in a serial order
		}
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}

int main(){
	pthread_mutex_init(&lock, NULL);
	pthread_t thread_num[NUM_THREADS] = {0}; // array of pthread identifiers
	int args[NUM_THREADS] = {0};

	for (int i=0; i < NUM_THREADS; i++)
	{
		args[i] = i;
		pthread_create(&thread_num[i], NULL, spin1, &args[i]);
	}

	//release all threads simultaneously:
	all_threads_are_created = true;

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_num[i],NULL);

	return 0;
}


