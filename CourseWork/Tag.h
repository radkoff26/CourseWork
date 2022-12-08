#pragma once
#include <iostream>

class Tag {
private:
	int id;
	std::string title;
public:
	Tag() {};
	Tag(int, std::string);
	int getId();
	void setId(int);
	std::string getTitle();
	void setTitle(std::string);
};