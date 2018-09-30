// ENSC 351 Lab 2
// implement 3 locks

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int counter = 0;
pthread_t thread_num[1000] = {0}; // array of pthread identifiers
bool doorArray[10000] = {0};

// method 2: array of 10,000 boolean variables

void* spin2(void* val){
	//cout << "in spin" << endl;
	
	int* thread_cond = (int*)val; //cast void parameter into int for while condition
	while(*thread_cond) {}

	while (counter < 10000){
		if(doorArray[counter] == 1){
			doorArray[counter+1] = 1;
			counter++;
		}
	}
}

int main(){
	//create 1000 pthreads - all spin on one variable
	int all_threads_are_created = 1; // all threads initially spin on this variable

	for (int i=0;i<1000;i++)
	{
		pthread_create(&thread_num[i], NULL, spin2, &all_threads_are_created);
	}

	//release all threads simultaneously:
	all_threads_are_created = 0;
	doorArray[0] = 1;

	cout << counter << endl;
	while (counter < 10000){}
	cout << counter << endl;

	return 0;
}