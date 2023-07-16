#include <iostream>
#include <string.h>
#include "parser.h"
#include "instruction.h"

int main(int argc, char *argv[])
{  
    std::string output;

    if (argc >= 2)
    {
        std::string file1(argv[1]);
        diff::parsers::parser p1;        
        diff::blocks::instruction a = p1.load(file1);

        if(!a.isempty())
        {
            std::string file2(argv[2]);
            diff::parsers::parser p2;        
            diff::blocks::instruction b = p2.load(file2);

            if(!b.isempty())
            {
                diff::blocks::instruction c = a.compare(b);
                output = c.output();
            }        
        }
    }

    std::cout << output;
     
    return 0;
}