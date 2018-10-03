// ENSC 351 Lab 2
// implement 3 locks

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "tracelib.h"

#define NUM_THREADS 1000

using namespace std;

bool all_threads_are_created = false;

int theDoor = 0;
pthread_mutex_t lock;

//trace stuff
char name[20];
char cat[20];
char filename[20] = "m1trace.json";


// method 1: single pthread_lock
// can't find pthread_lock... use pthread_mutex_lock?
//yup, i think that is what he meant

void* spin1(void* val){

	while(!all_threads_are_created);
	pthread_mutex_lock(&lock);

	trace_instant_global("door_entry");
	theDoor += 1;

	
//	cerr<<"Thread "<<theDoor<<" has locked the mutex."<<endl; //each thread should print this once in a serial order
	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}

int main(){

	// set up traces
    trace_start(filename);

	pthread_mutex_init(&lock, NULL);
	pthread_t thread_num[NUM_THREADS] = {0}; // array of pthread identifiers

	
    sprintf(name, "main trace");
    sprintf(cat, "foo");
    trace_event_start(name,cat, nullptr);

	for (int i=0; i < NUM_THREADS; i++)
	{
		pthread_create(&thread_num[i], NULL, spin1, NULL);
	}

	//release all threads simultaneously:
	sprintf(name, "release threads");
    sprintf(cat, "foo");
    trace_event_start(name,cat, nullptr);
	all_threads_are_created = true;


	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_num[i],NULL);


	trace_event_end(nullptr);//release threads trace
	trace_event_end(nullptr);//main trace

	trace_end();

	return 0;
}