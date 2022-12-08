#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include "Repository.h"

const std::string noteInsertionQuery = 
"INSERT INTO note (title, text, creation_time, modification_time) VALUES (?, ?, ?, ?)";

const std::string noteSelectionQuery = 
"SELECT * FROM note";

const std::string tagInsertionQuery = 
"INSERT INTO note_tag_relation (note_id, tag_id) VALUES (?, ?)";

void Repository::close()
{
	con->close();
}

std::vector<Note> Repository::findAllNotes()
{
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* rs = stmt->executeQuery(noteSelectionQuery);

	std::vector<Note> notes;

	while (rs->next()) {
		Note note;

		note.setId(rs->getInt("id"));
		note.setTitle(rs->getString("title"));
		note.setText(rs->getString("text"));
	}
}

void Repository::addNote(Note note)
{
	sql::PreparedStatement* ps = this->con->prepareStatement(noteInsertionQuery);

	time_t now = time(NULL);

	ps->setString(1, note.getTitle());
	ps->setString(2, note.getText());
	ps->setBigInt(3, std::to_string(now));
	ps->setBigInt(4, std::to_string(now));

	int id = ps->executeUpdate();

	ps->close();

	delete[] ps;

	if (note.getTags().size() > 0) {
		ps = this->con->prepareStatement(tagInsertionQuery);

		std::vector<Tag> tags = note.getTags();

		std::for_each(tags.begin(), tags.end(), [id, ps](Tag tag) {
			ps->setInt(1, id);
			ps->setInt(2, tag.getId());
			ps->execute();
			});

		ps->close();

		delete[] ps;
	}
}
