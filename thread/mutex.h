#pragma once

#include<pthread.h>
#include<unistd.h>
#include<deque>
#include<iostream>
#include<vector>
#include<errno.h>
#include<cstring>

using namespace std;

class Mutex
{
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
	pthread_mutex_t* getMutex();
private:
	pthread_mutex_t mLock;
	volatile bool locked;
};
