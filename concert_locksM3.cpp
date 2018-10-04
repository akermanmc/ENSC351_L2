// ENSC 351 Lab 2
// implement 3 locks

// method 3: ticket lock

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <atomic>
#include "tracelib.h"

#define NUM_THREADS 1000 //1000 is too heavy on Surface, laptop locks up

using namespace std;

bool all_threads_are_created = false;
int theDoor = 0;
int now_serving = 0;
atomic<int> next_ticket(0);

//trace stuff
char name[20];
char cat[20];
char filename[20] = "m3trace.json";

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

	while(!all_threads_are_created);

	tickeLock_aquire();
	theDoor++;
//	cerr<<"Thread "<<theDoor<<" has gone through the door."<<endl; //each thread should print this once in a serial order
	ticketLock_release();
	pthread_exit(NULL);
}

int main(){ 
	// set up traces
    trace_start(filename);
	pthread_t thread_num[NUM_THREADS] = {0}; // array of pthread identifiers

    sprintf(name, "main trace");
    sprintf(cat, "foo");
    trace_event_start(name,cat, nullptr);

	for (int i=0; i < NUM_THREADS; i++)
	{
		pthread_create(&thread_num[i], NULL, spin3, NULL);
	}

	//release all threads simultaneously:
	all_threads_are_created = true;
	sprintf(name, "release threads");
    sprintf(cat, "foo");
    trace_event_start(name,cat, nullptr);

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_num[i],NULL);

	trace_event_end(nullptr);//release threads trace
	trace_event_end(nullptr);//main trace

	trace_end();

	return 0;
}