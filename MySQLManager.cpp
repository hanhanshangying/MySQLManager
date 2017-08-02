#include "MySQLManager.h"    
using namespace mySql;

MySQLManager::MySQLManager(string hosts, string userName, string password, string dbName, unsigned int port)
{
	IsConnected = false;
	this->setHosts(hosts);             
	this->setUserName(userName);           
	this->setPassword(password);            
	this->setDBName(dbName);            
	this->setPort(port);            

	//mysql_library_init(0, 0, 0);
}

MySQLManager::~MySQLManager()
{
	this->destroyConnection();
}

void MySQLManager::setDBName(string dbName)
{
	if (dbName.empty())
	{
		std::cout << "DBName is null! Used default value: mysql" << std::endl;
		this->DBNAME = new char[5];
		strcpy(this->DBNAME, "mysql");
	}
	else
	{
		this->DBNAME = new char[dbName.length()];
		strcpy(this->DBNAME, dbName.c_str());
	}
}

void MySQLManager::setHosts(string hosts)
{
	if (hosts.empty())
	{    
		std::cout << "Hosts is null! Used default value: localhost" << std::endl;
		this->HOSTS = new char[9];
		strcpy(this->HOSTS, "localhost");
	}
	else
	{
		this->HOSTS = new char[hosts.length()];
		strcpy(this->HOSTS, hosts.c_str());
	}
}

void MySQLManager::setPassword(string password)
{   
	if (password.empty())
	{
		std::cout << "Password is null! Used default value: " << std::endl;
		this->PASSWORD = new char[1];
		strcpy(this->PASSWORD, "");
	}
	else
	{
		this->PASSWORD = new char[password.length()];
		strcpy(this->PASSWORD, password.c_str());
	}
}

void MySQLManager::setPort(unsigned int port)
{   
	if (port <= 0)
	{
		std::cout << "Port number is null! Used default value: 0" << std::endl;
		this->DEFAULTPORT = 0;
	}
	else
	{
		this->DEFAULTPORT = port;
	}
}

void MySQLManager::setUserName(string userName)
{  
	if (userName.empty())
	{
		std::cout << "UserName is null! Used default value: root" << std::endl;
		this->USERNAME = new char[4];
		strcpy(this->USERNAME, "root");
	}
	else
	{
		this->USERNAME = new char[userName.length()];
		strcpy(this->USERNAME, userName.c_str());
	}
}

void MySQLManager::initConnection()
{
	//han changed
	if (IsConnected)
	{    
		std::cout << "Is connected to server!" << std::endl;
		return;
	}
	//mysql_thread_init();
	//if (!mysql_thread_safe())
	//{
	//	cout << "MCS uses MySQL from multiple threads - you MUST link with a thread safe version of the mySQL client library!";
	//}
	//else
	{
		MYSQL * con = mysql_init(&mySQLClient);  
		if (con == NULL)
		{
			cout << "-----------------------------" << endl;
			std::cout << "init MYSQL object fail.\n" << mysql_error(&mySQLClient) << std::endl;
		}
		if (!mysql_real_connect(&mySQLClient, HOSTS, USERNAME, PASSWORD, DBNAME, DEFAULTPORT, NULL, 0))
		{
			cout << "-----------------------------" << endl;
			std::cout << "Error connection to database: \n" << mysql_error(&mySQLClient) << std::endl;
		}
		IsConnected = true;    
	}
}

bool MySQLManager::runSQLQuery(string sql)
{
	if (!IsConnected)
	{ 
		std::cout << "Not connect to database!" << std::endl;
		return false;
	}
	if (sql.empty())
	{    
		std::cout << "SQL statement is null!" << std::endl;
		return false;
	}

	MYSQL_RES *res;
	MYSQL_ROW row;

	unsigned int i, j = 0;

	i = mysql_real_query(&mySQLClient, sql.c_str(), (unsigned int)strlen(sql.c_str()));   
	if (i < 0)
	{
		std::cout << "Error query from database: \n" << mysql_error(&mySQLClient) << std::endl;
		return false;
	}
	res = mysql_store_result(&mySQLClient);
	vector<string> objectValue;
	while ((row = mysql_fetch_row(res)))
	{    
		objectValue.clear();
		for (j = 0; j < mysql_num_fields(res); j++)
		{
			objectValue.push_back(row[j]);
		}
		this->resultList.push_back(objectValue);
	}
	mysql_free_result(res);         //free result after you get the result    

	return true;
}

unsigned int MySQLManager::insert(std::string sql)
{
	if (!IsConnected) 
	{
		cout << "Not connect to database!" << endl;
		return -1;
	}
	if (sql.empty())
	{
		cout << "sql is null " << endl;
		return -1;
	}
	int rows = -1;
	int res = mysql_query(&mySQLClient, sql.c_str());

	cout << "PS:mysql_errno: " << mysql_errno(&mySQLClient) << "," << mysql_error(&mySQLClient) << endl;
	if (res >= 0)
	{
		rows = mysql_affected_rows(&mySQLClient);
		cout << "Inserted " << rows << " rows\n";
		return rows;
	}
	else 
	{
		cout << "Insert error " << mysql_errno(&mySQLClient) << "," << mysql_error(&mySQLClient) << endl;
		return -1;
	}
}

unsigned int MySQLManager::insert1(std::string sql)
{
	if (!IsConnected) 
	{
		cout << "Not connect to database!" << endl;
		return -1;
	}
	if (sql.empty())
	{
		cout << "sql is null " << endl;
		return -1;
	}
	int rows = -1;
	int res = mysql_real_query(&mySQLClient, sql.c_str(), (unsigned int)strlen(sql.c_str()));
	if (res = 0)
	{
		rows = mysql_affected_rows(&mySQLClient);
		cout << "Inserted " << rows << " rows\n";
		return rows;
	}
	else 
	{
		cout << "Insert error " << mysql_errno(&mySQLClient) << "," << mysql_error(&mySQLClient) << endl;
		return -1;
	}
}

vector< vector<string> > MySQLManager::getResult()
{
	return resultList;
}

void MySQLManager::destroyConnection()
{
	//mysql_thread_end();
	mysql_close(&mySQLClient);
	this->IsConnected = false;
}

bool MySQLManager::getConnectionStatus()
{
	return IsConnected;
}
