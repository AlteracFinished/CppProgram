#include "mutex.h"

Mutex::Mutex()
{
	pthread_mutex_init(&mLock,NULL);
	locked=false;
}

Mutex::~Mutex()
{
	while(locked);
	unlock();
	pthread_mutex_destroy(&mLock);
}

void Mutex::lock()
{
	pthread_mutex_lock(&mLock);
	locked=true;
}

void Mutex::unlock()
{
	locked=false;
	pthread_mutex_unlock(&mLock);
}

pthread_mutex_t* Mutex::getMutex()
{
	return &mLock;
}
