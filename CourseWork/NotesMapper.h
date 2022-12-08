#pragma once
#include "Mapper.h"
#include "Note.h"

class NotesMapper : public Mapper<Note>
{
public:
	NotesMapper() {}
	Note map(std::unique_ptr<sql::ResultSet>) override;
};

