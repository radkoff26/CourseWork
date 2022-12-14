#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include "Repository.h"
#include "NotesMapper.h"
#include "TagMapper.h"

const std::string noteInsertionQuery = 
"INSERT INTO note (title, text, creation_time, modification_time, author) VALUES (?, ?, ?, ?, ?)";

const std::string noteSelectionQuery = 
"SELECT * FROM note";

const std::string tagNoteRelationInsertionQuery = 
"INSERT INTO note_tag_relation (note_id, tag_id) VALUES (?, ?)";

const std::string tagSelectionQuery =
"SELECT * FROM tag";

const std::string tagInsertionQuery =
"INSERT INTO tag (title) VALUES (?)";

const std::string deletionNoteQuery =
"DELETE FROM note WHERE id=?";

const std::string deletionNoteRelationQuery =
"DELETE FROM note_tag_relation WHERE note_id=?";

const std::string updatingNoteQuery =
"UPDATE note set title=?, text=?, modification_time=?, author=? WHERE id=?";

const std::string authorStatsQuery =
"SELECT author, COUNT(*) as count from note GROUP BY author";

const std::string tagCountQuery =
"SELECT COUNT(*) as count from note_tag_relation WHERE tag_id=?";

void Repository::close()
{
	con->close();
}

std::vector<Note> Repository::findAllNotes(std::vector<std::function<bool(Note)>> filters)
{
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* rs = stmt->executeQuery(noteSelectionQuery);

	std::vector<Note> notes;

	NotesMapper mapper(con);

	while (rs->next()) {
		notes.push_back(mapper.map(rs));
	}

	delete[] stmt;
	delete[] rs;

	if (filters.size() == 0) {
		return notes;
	}

	std::vector<Note> result;

	for (int i = 0; i < notes.size(); i++)
	{
		Note note = notes[i];

		bool flag = true;

		for (int j = 0; j < filters.size(); j++)
		{
			if (!filters[j](note)) {
				flag = false;
				break;
			}
		}

		if (flag) {
			result.push_back(note);
		}
	}

	return result;
}

void Repository::addNote(Note note)
{
	sql::PreparedStatement* ps = this->con->prepareStatement(noteInsertionQuery);

	time_t now = time(NULL);

	ps->setString(1, note.getTitle());
	ps->setString(2, note.getText());
	ps->setBigInt(3, std::to_string(now));
	ps->setBigInt(4, std::to_string(now));
	ps->setString(5, note.getAuthor());

	int id;

	ps->executeQuery();

	sql::Statement* stmt = con->createStatement();

	sql::ResultSet* inserted = stmt->executeQuery("SELECT * FROM note ORDER BY id DESC LIMIT 1");

	if (inserted->next()) {
		id = inserted->getInt("id");
	}

	ps->close();

	delete[] stmt;
	delete[] inserted;
	delete[] ps;

	if (note.getTags().size() > 0) {
		ps = this->con->prepareStatement(tagNoteRelationInsertionQuery);

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

std::vector<Tag> Repository::findAllTags()
{
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* rs = stmt->executeQuery(tagSelectionQuery);

	std::vector<Tag> tags;

	TagMapper mapper;

	while (rs->next()) {
		tags.push_back(mapper.map(rs));
	}

	delete[] stmt;
	delete[] rs;

	return tags;
}

void Repository::addTag(Tag tag)
{
	sql::PreparedStatement* ps = this->con->prepareStatement(tagInsertionQuery);

	ps->setString(1, tag.getTitle());

	ps->execute();

	delete[] ps;
}

int Repository::countTagRelationsByTagId(int id)
{
	sql::PreparedStatement* ps = con->prepareStatement(tagCountQuery);

	ps->setInt(1, id);

	sql::ResultSet* rs = ps->executeQuery();

	int count;

	if (rs->next()) {
		count = rs->getInt("count");
	}

	delete[] ps;
	delete[] rs;

	return count;
}

void Repository::updateNote(Note note)
{
	sql::PreparedStatement* ps = this->con->prepareStatement(updatingNoteQuery);

	ps->setString(1, note.getTitle());
	ps->setString(2, note.getText());
	ps->setBigInt(3, std::to_string(note.getModificationTime()));
	ps->setString(4, note.getAuthor());
	ps->setInt(5, note.getId());

	ps->executeUpdate();

	delete[] ps;
}

void Repository::deleteNote(int id)
{
	sql::PreparedStatement* ps = this->con->prepareStatement(deletionNoteQuery);

	ps->setInt(1, id);

	ps->executeUpdate();

	delete[] ps;

	ps = this->con->prepareStatement(deletionNoteRelationQuery);

	ps->setInt(1, id);

	ps->executeUpdate();

	delete[] ps;
}

std::map<std::string, int> Repository::countAuthorsNotesGrouped()
{
	std::map<std::string, int> map;

	sql::Statement* stmt = con->createStatement();

	sql::ResultSet* rs = stmt->executeQuery(authorStatsQuery);

	while (rs->next()) {
		map.insert(std::pair<std::string, int>(rs->getString("author"), rs->getInt("count")));
	}

	delete[] stmt;
	delete[] rs;

	return map;
}
