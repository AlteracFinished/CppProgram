#pragma once

#include<iostream>
#include<vector>
#include<functional>
using namespace std;
namespace _alt
{
	template<typename R,typename...Args> class _Task
	{
	public:
		_Task(function<R(Args...)>&,Args...args);
		R run();
	private:
		function<R(Args...)> func;
	};
}
template<typename R> class Task
{
public:
	Task(function<R>);
	~Task();
	void operator()();
	void run();
private:
	function<R> taskFunc;
};
