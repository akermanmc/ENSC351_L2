// ENSC 351 Lab 2
// implement 3 locks

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;
int counter = 0;
pthread_mutex_t lock;


// method 1: single pthread_lock
// can't find pthread_lock... use pthread_mutex_lock?
void* spin1(void* val){
	//cout << "in spin" << endl;
	
	int* thread_cond = (int*)val; //cast void parameter into int for while condition
	while(*thread_cond) {}

	while(counter < 10000){
		pthread_mutex_lock(&lock);
		if (counter < 10000)
			counter +=1;
		//cout << counter << endl;
		pthread_mutex_unlock(&lock);
	}
}

int main(){
	//create 1000 pthreads - all spin on one variable
	int all_threads_are_created = 1; // all threads initially spin on this variable
	pthread_t thread_num[1000] = {0}; // array of pthread identifiers

	pthread_mutex_init(&lock, NULL);

	for (int i=0;i<1000;i++)
	{
		pthread_create(&thread_num[i], NULL, spin1, &all_threads_are_created);
	}

	//release all threads simultaneously:
	all_threads_are_created = 0;

	// wait for threads to pass through counter
	cout << counter << endl;
	while (counter < 10000){}
	cout << counter << endl;


	return 0;
}


