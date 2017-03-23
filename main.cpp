#include<iostream>
#include "headers.h"
using namespace std;

void out(int number)
{
	cout << number << endl;
}

int main(int argc,char* argv[])
{
	Mutex* mutex = new Mutex();
	int number = 1;
	Task* task = new Task(out,number);
	task->run();
	mutex->lock();
	out(1);
	mutex->unlock();
  return 0;
}
