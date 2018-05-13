#ifndef MYSQLMANAGER_H_    
#define MYSQLMANAGER_H_
//#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "mysql.h"    
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
		MySQLManagerstring hosts,string userName, string password, string dbName, unsigned int port);
		~MySQLManager();
		void initConnection();
		/*
		* Making query from database
		* @param sql:          Running SQL command
		* @return:    Success of Fail
		*/
		bool runSQLQuery(string sql);
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
		void setUserName(string userName);
		void setHosts(string hosts);
		void setPassword(string password);
		void setDBName(string dbName);
		void setPort(unsigned int port);
		
	private:
		bool IsConnected;
		vector< vector<string> > resultList;
		MYSQL mySQLClient;
		unsigned int DEFAULTPORT;
		string HOSTS;
		string USERNAME;
		string PASSWORD;
		strung DBNAME;
	};
}
#endif /* MYSQLMANAGER_H_ */
