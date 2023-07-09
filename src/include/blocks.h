#include <string>
#include <vector>

#ifndef _DIFF_BLOCKS
#define _DIFF_BLOCKS

namespace diff
{
    namespace blocks
    {
        class block
        {
        public:
            std::string identifier;
            
            std::vector<std::string> instructions;
            std::vector<block> children;

        public:            
            block() { }
            ~block() { }

            void compare(block source);

        public:
            void clear();
        };
    };
};

#endif