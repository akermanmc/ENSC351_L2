// ENSC 351 Lab 2
// implement 3 locks

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <tracelib.h>

#define NUM_THREADS 1000 //1000 is too heavy on Surface, laptop locks up

using namespace std;

bool all_threads_are_created = false;
int theDoor = 0;
bool PeopleArray[NUM_THREADS] = {false};

void* spin2(void* val){
    //get the thread number
    int threadNum = *(int*)val;

	while(!all_threads_are_created);

	while(!PeopleArray[threadNum]);
	theDoor += 1;
//	cerr<<"Thread "<<threadNum<<" has gone through the door."<<endl; //each thread should print this once in a serial order
    PeopleArray[(threadNum + 1)%NUM_THREADS] = true;
	pthread_exit(NULL);
}

int main(){
	pthread_t thread_num[NUM_THREADS] = {0}; // array of pthread identifiers
	int thread_args[NUM_THREADS] = {0};

	for (int i=0; i < NUM_THREADS; i++)
	{
	    thread_args[i] = i;
		pthread_create(&thread_num[i], NULL, spin2, &thread_args[i]);
	}

	//release all threads simultaneously:
	all_threads_are_created = true;
	//set the first person to go through:
    PeopleArray[0] = true;

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_num[i],NULL);

	return 0;
}