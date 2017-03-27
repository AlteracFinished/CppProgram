#include<iostream>
#include "headers.h"
using namespace std;

void out(int number)
{
	cout << number << endl;
}

int main(int argc,char* argv[])
{
	ThreadPool* threadPool = new ThreadPool(2);
	int number=1;
	Task* task = new Task(&out,number);
	threadPool->addTask(task);
	sleep(5);
  return 0;
}
