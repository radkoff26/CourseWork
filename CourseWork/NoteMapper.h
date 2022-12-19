#pragma once
#include "Mapper.h"
#include "Repository.h"
#include "Note.h"

class NoteMapper : public Mapper<Note>
{
public:
	NoteMapper(sql::Connection* connection): connection(connection) {}
	~NoteMapper() {
		this->connection = nullptr;
	}
	Note map(sql::ResultSet* rs) override;
private:
	sql::Connection* connection;
};

