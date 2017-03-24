#include "condVar.h"

CondVar::CondVar()
{
	pthread_cond_init(&mCondVar,NULL);
}

CondVar::~CondVar()
{
	pthread_cond_destroy(&mCondVar);
}

void CondVar::wait(pthread_mutex_t* mutex)
{
	pthread_cond_wait(&mCondVar,mutex);
}

void CondVar::signal()
{
	pthread_cond_signal(&mCondVar);
}

void CondVar::broadcast()
{
	pthread_cond_broadcast(&mCondVar);
}
