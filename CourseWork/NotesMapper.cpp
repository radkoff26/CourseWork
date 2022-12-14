#include "NotesMapper.h"
#include "TagMapper.h"

Note NotesMapper::map(sql::ResultSet* rs)
{
    Note note;
	sql::PreparedStatement* psRel = connection->prepareStatement("SELECT * FROM note_tag_relation WHERE note_id=?");
	sql::PreparedStatement* psTag = connection->prepareStatement("SELECT * FROM tag WHERE id=?");

	int id = rs->getInt("id");

	note.setId(id);
	note.setTitle(rs->getString("title"));
	note.setText(rs->getString("text"));

	psRel->setInt(1, id);

	sql::ResultSet* rsRelation = psRel->executeQuery();

	std::vector<Tag> tags;

	TagMapper mapper;

	while (rsRelation->next()) {
		psTag->setInt(1, rsRelation->getInt("tag_id"));
		sql::ResultSet* result = psTag->executeQuery();
		if (result->next()) {
			tags.push_back(mapper.map(result));
		}
		delete[] result;
	}

	note.setTags(tags);

	note.setCreationTime(rs->getInt64("creation_time"));
	note.setModificationTime(rs->getInt64("modification_time"));
	note.setAuthor(rs->getString("author"));

	delete[] psRel;
	delete[] psTag;

	return note;
}
