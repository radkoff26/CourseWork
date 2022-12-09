#pragma once
#include "Mapper.h"
#include "Tag.h"

class TagMapper: public Mapper<Tag>
{
public:
	Tag map(sql::ResultSet* rs) override;
};

