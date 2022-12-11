#include "Note.h"

Note::Note(
    int id, std::string title,
    std::string text, std::vector<Tag> tags,
    time_t creationTime,
    time_t modificationTime
) : id(id), title(title), text(text), tags(tags),
    creationTime(creationTime), modificationTime(modificationTime)
{}

int Note::getId()
{
    return id;
}

void Note::setId(int id)
{
    this->id = id;
}

std::string Note::getTitle()
{
    return title;
}

void Note::setTitle(std::string title)
{
    this->title = title;
}

std::string Note::getText()
{
    return text;
}

void Note::setText(std::string text)
{
    this->text = text;
}

std::vector<Tag> Note::getTags()
{
    return tags;
}

void Note::setTags(std::vector<Tag> tags)
{
    this->tags = tags;
}

time_t Note::getCreationTime()
{
    return creationTime;
}

void Note::setCreationTime(time_t creationTime)
{
    this->creationTime = creationTime;
}

time_t Note::getModificationTime()
{
    return modificationTime;
}

void Note::setModificationTime(time_t modificationTime)
{
    this->modificationTime = modificationTime;
}

std::string Note::getTagsStringified()
{
    std::string s = "";
    if (tags.size() > 0) {
        for (int i = 0; i < tags.size(); i++)
        {
            s += (s.size() > 0 ? ", " : "") + tags[i].getTitle();
        }
    }
    else {
        s = "None";
    }
    return s;
}
