#include "task.h"

using namespace std;

template<typename R,typename...Args>
Task::Task(R&& func,Args&& ...args)
{
	taskFunc=bind(forward<R>(func),args...);
}

Task::~Task(){}

void Task::operator()()
{
	taskFunc();
}

void Task::run()
{
	taskFunc();
}


