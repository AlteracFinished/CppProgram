#pragma once

#include<pthread.h>

class CondVar
{
	public:
		CondVar();
		~CondVar();
		void wait(pthread_mutex_t*);
		void signal();
		void broadcast();
	private:
		pthread_cond_t mCondVar;
};
