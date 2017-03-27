#include"threadPool.h"

ThreadPool::ThreadPool(int size=DEFAULT_POOL_SIZE):poolSize(size)
{
	poolState=1;
	int ret = -1;
	for(int i = 0;i<poolSize;++i)
	{
		pthread_t t;
		ret = pthread_create(&t,NULL,_exec_thread,this);
		if(ret!=0)
		{
			cout << "thread create error" << endl;
			exit(1);
		}
		threads.push_back(t);
	}
}

ThreadPool::~ThreadPool()
{
	if(poolState!=0)
	{
		mutex.lock();
		poolState=0;
		mutex.unlock();
		condVar.broadcast();

		int ret=-1;
		for(int i = 0;i<poolSize;i++)
		{
			void* res;
			pthread_join(threads[i],&res);
			cout << "thread return" << res << ":" << endl;
			condVar.broadcast();
		}
	}
}

void ThreadPool::execThread()
{
	Task* task=NULL;
	while(true)
	{
		mutex.lock();
		while((poolState!=0)&&(tasks.empty()))
		{
			condVar.wait(mutex.getMutex());
		}
		if(poolState==0)
		{
			mutex.unlock();
			pthread_exit(NULL);
		}
		task=tasks.front();
		tasks.pop_front();
		mutex.unlock();
		(*task)();
		delete task;
	}
}

void ThreadPool::addTask(Task* task)
{
	mutex.lock();
	tasks.push_back(task);
	condVar.signal();
	mutex.unlock();
}

void* ThreadPool::_exec_thread(void* tp)
{
	((ThreadPool*)tp)->execThread();
	return NULL;
}

