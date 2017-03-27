#pragma once

#include<pthread.h>
#include<unistd.h>
#include<vector>
#include<deque>
#include<iostream>
#include<functional>

#include"mutex.h"
#include"task.h"
#include"condVar.h"
#include"threadConfig.h"

using namespace std;

class ThreadPool
{
	public:
		ThreadPool(int);
		~ThreadPool();
		void execThread();
		void addTask(Task* task);
	private:
		static void* _exec_thread(void*);
		int poolSize;
		Mutex mutex;
		CondVar condVar;
		vector<pthread_t> threads;
		deque<Task*> tasks;
		volatile int poolState;
};
