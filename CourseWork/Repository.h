#pragma once
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

const std::string server = "127.0.0.1:3306";
const std::string username = "root";
const std::string password = "123456789";

class Repository
{
private:
	sql::Driver* driver;
	sql::Connection* con;
public:
	Repository() {
		try
		{
			this->driver = get_driver_instance();
			this->con = this->driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
			system("pause");
			exit(1);
		}
	}
	~Repository() {
		if (con != nullptr) {
			if (!con->isClosed()) {
				con->close();
			}
			delete[] con;
		}
	}
	void close();
};

