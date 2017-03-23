#include "task.h"

using namespace std;

template<typename R,typename...Args>
_alt::_Task<R,Args...>::_Task(function<R(Args...)>& execFunc,Args...args)
{
	func=execFunc;
	bind(&func,args...);
}

template<typename R,typename...Args>
R _alt::_Task<R,Args...>::run()
{
	func();
}

template<typename R>
Task<R>::Task(function<R> func)
{
	taskFunc=func;	
}

template<typename R>
Task<R>::~Task(){}

template<typename R>
void Task<R>::operator()()
{
	
}
template<typename R>
void Task<R>::run()
{
}


