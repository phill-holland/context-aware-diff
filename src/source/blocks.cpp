#include "blocks.h"

void diff::blocks::block::clear()
{
    identifier.clear();
    instructions.clear();
    children.clear();
}
