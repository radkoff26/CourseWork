#include "TagMapper.h"

Tag TagMapper::map(sql::ResultSet* rs)
{
    Tag tag;

    tag.setId(rs->getInt("id"));
    tag.setTitle(rs->getString("title"));

    return tag;
}
