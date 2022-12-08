#pragma once
#include <iostream>
#include <vector>
#include "Tag.h"

class Note {
private:
	int id;
	std::string title;
	std::string text;
	std::vector<Tag> tags;
	time_t creationTime;
	time_t modificationTime;
public:
	Note(){}
	Note
	(
		int id, std::string title,
		std::string text, std::vector<Tag> tags,
		time_t creationTime, time_t modificationTime
	);
	int getId();
	void setId(int);
	std::string getTitle();
	void setTitle(std::string);
	std::string getText();
	void setText(std::string);
	std::vector<Tag> getTags();
	void setTags(std::vector<Tag>);
	time_t getCreationTime();
	void setCreationTime(time_t);
	time_t getModificationTime();
	void setModificationTime(time_t);
};

