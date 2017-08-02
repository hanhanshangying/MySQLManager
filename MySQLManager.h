#ifndef MYSQLMANAGER_H_    
#define MYSQLMANAGER_H_     
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "MySQLConnectorC/include/mysql.h"    
#include <string>    
#include <iostream>    
#include <vector>    
#include <string.h>    

using namespace std;
namespace mySql
{

	class MySQLManager
	{
	public:
		/*
		* Init MySQL
		* @param hosts:           Host IP address
		* @param userName:        Login UserName
		* @param password:        Login Password
		* @param dbName:          Database Name
		* @param port:            Host listen port number
		*/
		MySQLManager(std::string hosts, std::string userName, std::string password, std::string dbName, unsigned int port);
		~MySQLManager();
		void initConnection();
		/*
		* Making query from database
		* @param sql:          Running SQL command
		* @return:    Success of Fail
		*/
		bool runSQLQuery(std::string sql);
		/*
		* Making insert from database
		* @param sql: Running SQL command
		* @return:    The number of rows affected
		*/
		unsigned int insert(std::string sql);
		unsigned int insert1(std::string sql);
		/**
		* Destroy MySQL object
		*/
		void destroyConnection();
		/**
		* Get MySQL connection status 
		*/
		bool getConnectionStatus();
		vector< vector<string> > getResult();
		MYSQL getMysql(){ return mySQLClient; }
	protected:
		void setUserName(std::string userName);
		void setHosts(std::string hosts);
		void setPassword(std::string password);
		void setDBName(std::string dbName);
		void setPort(unsigned int port);
		
	private:
		bool IsConnected;
		vector< vector<string> > resultList;
		MYSQL mySQLClient;
		unsigned int DEFAULTPORT;
		char * HOSTS;
		char * USERNAME;
		char * PASSWORD;
		char * DBNAME;
	};
}
#endif /* MYSQLMANAGER_H_ */
