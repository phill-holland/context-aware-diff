#include "blocks.h"
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
            blocks::block load(std::string filename);

        protected:
            blocks::block parse(std::string data);
        };
    };
};

#endif