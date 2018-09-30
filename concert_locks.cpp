// ENSC 351 Lab 2
// implement 3 locks

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* spin(void* val)
{
	//cout << "in spin" << endl;
	int* thread_cond = (int*)val;
	while(*thread_cond) {}
}

int main(){
	//create 1000 threads (pthreads?) - all spin on one variable?
	int all_threads_are_created = 1;
	pthread_t thread_num[1000] = {0};

	for (int i=0;i<1000;i++)
	{
		pthread_create(&thread_num[i], NULL, spin, &all_threads_are_created);
	}

	return 0;
}

// method 1: single pthread_lock


// method 2: array of 10,000 boolean variables


// method 3: single ticket lock