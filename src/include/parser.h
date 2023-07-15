#include "instruction.h"
#include <string>

#ifndef _DIFF_PARSER
#define _DIFF_PARSER

namespace diff
{
    namespace parsers
    {
        class parser
        {
        public:            
            parser() { }            
            ~parser() { }
            
        public:
            blocks::instruction load(std::string filename);
            blocks::instruction parse(std::string data);
        };
    };
};

#endif