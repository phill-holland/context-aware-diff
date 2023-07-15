#include <string>
#include <vector>

#ifndef _DIFF_INSTRUCTION
#define _DIFF_INSTRUCTION

namespace diff
{
    namespace blocks
    {
        class instruction
        {
        public:
            std::string instr;
            std::vector<instruction> children;

        public:            
            instruction() { }
            ~instruction() { }

        public:
            void clear();
            
            instruction compare(instruction source);
            instruction prefix(std::string value);
            
            std::string output();

            void save(std::string filename);
        };
    };
};

#endif