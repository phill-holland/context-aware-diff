#include "blocks.h"

void diff::blocks::block::clear()
{
    identifier.clear();
    instructions.clear();
    children.clear();
}

void diff::blocks::block::compare(block source)
{
    // for each instrsuction in source
    // find it's position in current instruction
    // is it in same position?
    // if not
    // insert or delete happened
    // are instructions after that one in source, in current
    // still in correct order after?

}

// children compare -- for functions/procs only, sort functions on both sides
// find new functions (function order not important)