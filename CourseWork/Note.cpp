#include "Note.h"

Note::Note(
    int id, std::string title,
    std::string text, int numberOfTags,
    Tag* tags, time_t creationTime,
    time_t modificationTime
) : id(id), title(title), text(text), numberOfTags(numberOfTags),
    tags(tags), creationTime(creationTime), modificationTime(modificationTime)
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

int Note::getNumberOfTags()
{
    return numberOfTags;
}

void Note::setNumberOfTags(int numberOfTags)
{
    this->numberOfTags = numberOfTags;
}

Tag* Note::getTags()
{
    return tags;
}

void Note::setTags(Tag* tags)
{
    if (tags != nullptr) {
        delete[] this->tags;
        this->tags = nullptr;
    }
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
