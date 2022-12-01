#include "Tag.h"

Tag::Tag(int id, std::string title): id(id), title(title)
{}

int Tag::getId()
{
    return id;
}

void Tag::setId(int id)
{
    this->id = id;
}

std::string Tag::getTitle()
{
    return title;
}

void Tag::setTitle(std::string title)
{
    this->title = title;
}
