#include<iostream>
#include<string>
#include<cstdlib>
#include<unistd.h>
#include<thread>

//using namespace std;

#define SIZE 2000000000
#define THREADS 10
char arr[SIZE];

void fill(int a, int b) {
	for(int i=a; i<b; i++) arr[i] = 'a'+(i%10);
}

int main()
{
	for(int i=0; i<SIZE; i++) arr[i] = 'a'+(i%10);

	//std::thread thethread (fill, 0, SIZE);
	//thethread.join();
/*
	std::thread tarr[THREADS];
	int amount = SIZE/THREADS;
	for(int i=0; i<THREADS; i++) {
		tarr[i] = std::thread(fill,i*amount, (i+1)*amount); 
	}
	
	for(int i=0; i<THREADS; i++) {
		tarr[i].join();
	}
*/
	//sleep(120);

	std::cout << "Done\n";
}
