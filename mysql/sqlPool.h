#pragma once

#include<mysql/mysql_connection.h>
#include<mysql/mysql_driver.h>
#include<mysql/cppconn/exception.h>
#include<mysql/cppconn/driver.h>
#include<mysql/cppconn/connection.h>
#include<mysql/cppconn/resultset.h>
#include<mysql/cppconn/prepared_statement.h>
#include<mysql/cppconn/statement.h>
#include<pthread.h>
#include<list>
#include<stdexcept>
#include<exception>
#include<stdio.h>
using namespace std;
using namespace sql;

class ConnPool{
private:  
	int curSize;
	int maxSize;
	string username;  
	string password;  
	string url;  
	list<Connection*> connList;
	pthread_mutex_t lock;
	static ConnPool *connPool;
	Driver* driver;  

	Connection* CreateConnection();
	ConnPool(stringurl,string user,string password,int maxSize);
public:  
	~ConnPool();  
	Connection* GetConnection();
	void ReleaseConnection(Connection *conn);
	static ConnPool *GetInstance();
};  