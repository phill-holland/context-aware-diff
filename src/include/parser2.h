#include "instruction.h"
#include <string>

#ifndef _DIFF_PARSER2
#define _DIFF_PARSER2

namespace diff
{
    namespace parsers
    {
        class parser2
        {
        public:            
            parser2() { }            
            ~parser2() { }
            
        public:
            blocks::instruction load(std::string filename);
            blocks::instruction parse(std::string data);
        };
    };
};

#endif