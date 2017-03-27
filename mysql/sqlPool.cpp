#include"sqlPool.h"  

using namespace std;
using namespace sql;
ConnPool::ConnPool(string url, string userName,string password, int maxSize)
{  
	this->maxSize=maxSize;  
	this->curSize=0;  
	this->username=userName;  
	this->password=password;  
	this->url=url;  
	try{  
		this->driver=sql::mysql::get_driver_instance();  
	}
	catch(sql::SQLException&e)  
	{  
	perror("connecting error;\n");  
	}  
	catch(std::runtime_error&e)  
	{  
		perror("runtime error\n");  
	}
	Connection* conn;
	pthread_mutex_lock(&lock);
	for(inti=0;i<maxSize/2;i++)
	{
		conn=this->CreateConnection();
		if(conn){
			connList.push_back(conn);  
			++(this->curSize);  
		}
		else
		{
			perror("create connector error");  
		}
	}
	pthread_mutex_unlock(&lock);
}
ConnPool*ConnPool::GetInstance(){  
	if(connPool==NULL)
	{
		connPool=new ConnPool("tcp://rm-2ze0p690d93cbn33yo.mysql.rds.aliyuncs.com","root","tour@123456",50);
	}
	return connPool;  
}
Connection*ConnPool::CreateConnection(){  
	Connection*conn;  
	try{  
		conn=driver->connect(this->url,this->username,this->password);
		return conn;  
	}  
	catch(sql::SQLException& e)  
	{  
		perror("create connector error");  
		return NULL;  
	}  
	catch(std::runtime_error& e)  
	{  
		perror("runtime error");  
		return NULL;  
	}  
}
Connection* ConnPool::GetConnection(){  
	Connection*con;  
	pthread_mutex_lock(&lock);  
	if(connList.size()>0)
	{  
		con=connList.front();
		connList.pop_front();
		if(con->isClosed())
		{  
			delete con;  
			con=this->CreateConnection();  
		}
		if(con==NULL)  
		{  
			--curSize;  
		}  
		pthread_mutex_unlock(&lock);  
		return con;  
	}  
	else{  
		if(curSize< maxSize){
			con= this->CreateConnection();  
			if(con){  
				++curSize;  
				pthread_mutex_unlock(&lock);  
				return con;  
			}  
			else{  
				pthread_mutex_unlock(&lock);  
				return NULL;  
			}  
		}  
		else{
			pthread_mutex_unlock(&lock);  
			return NULL;  
		}  
	}  
}
void ConnPool::ReleaseConnection(sql::Connection* conn){  
	if(conn){  
		pthread_mutex_lock(&lock);  
		connList.push_back(conn);  
		pthread_mutex_unlock(&lock);  
	}  
}
ConnPool::~ConnPool()  
{  
	list<Connection*>::iterator icon;  
	pthread_mutex_lock(&lock);  
	for(icon=connList.begin();icon!=connList.end();++icon)  
	{  
		this->DestoryConnection(*icon);
		if(*icon)  
		{  
			try{  
				(*icon)->close();  
			}  
			catch(sql::SQLException&e)  
			{  
				perror(e.what());  
			}  
			catch(std::exception&e)  
			{  
				perror(e.what());  
			}  
			delete *icon;  
		}
	}  
	curSize=0;  
	connList.clear();
	pthread_mutex_unlock(&lock);
}