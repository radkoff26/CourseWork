#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

template <class T>
class Mapper
{
public:
	virtual T map(std::unique_ptr<sql::ResultSet>) {};
protected:
	Mapper() {}
};

