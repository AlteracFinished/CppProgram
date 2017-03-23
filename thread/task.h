#pragma once

#include<iostream>
#include<vector>
#include<functional>
using namespace std;

class Task
{
public:
	template<typename Func,typename...Args>
	explicit Task(Func&&,Args&&...);
	~Task();
	void operator()();
	void run();
private:
	function<void()> taskFunc;
};
