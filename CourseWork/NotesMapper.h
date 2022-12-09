#pragma once
#include "Mapper.h"
#include "Repository.h"
#include "Note.h"

class NotesMapper : public Mapper<Note>
{
public:
	NotesMapper(sql::Connection* connection): connection(connection) {}
	Note map(sql::ResultSet* rs) override;
private:
	sql::Connection* connection;
};

