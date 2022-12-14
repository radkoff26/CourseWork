#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Note.h"
#include "Tag.h"

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
			this->con->setSchema("coursework");
		}
		catch (sql::SQLException e)
		{
			std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
			system("pause");
			exit(1);
		}
	}
	~Repository() {

	}
	void close();
	// Note
	std::vector<Note> findAllNotes(std::vector<std::function<bool(Note)>> filters);
	void addNote(Note note);
	void updateNote(Note note);
	void deleteNote(int id);
	std::map<std::string, int> countAuthorsNotesGrouped();
	// Tag
	std::vector<Tag> findAllTags();
	void addTag(Tag tag);
	int countTagRelationsByTagId(int id);
};

