#include "parser.h"
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

diff::blocks::instruction diff::parsers::parser::load(std::string filename)
{
    diff::blocks::instruction result;

    ifstream source(filename, ios::in | ios::binary);
    if(!source) return result;

    const int sz = 4096;
    char buffer[sz];

    std::string data;

    int read = 0;
    do
    {
        read = source.readsome(buffer, sz);
        if(read > 0) data.append(std::string(buffer, read));
    }while (read > 0);

    if(data.size() > 0) result = parse(data);

    return result;
}

diff::blocks::instruction diff::parsers::parser::parse(std::string data)
{
    diff::blocks::instruction result;
    std::stack<diff::blocks::instruction*> stack;
    
    stack.push(&result);

    char p;
    std::string current;
    int quote_state = 0, line_state = 0;

    for(std::string::iterator it = data.begin(); it != data.end(); ++it)
    {        
        if(*it == 13) { }
        else if((*it == ' ') && ((p == ' ')||(p == 10)) && (quote_state == 0)) { }
        else if(*it == 10)
        {
            if(line_state == 0) ++line_state;
        }
        else if(*it == '"')
        {
            if(quote_state == 0) ++quote_state;
            else if (quote_state == 1)
            {
                if(p != '\\') quote_state = 0;
            }
            current.push_back(*it);
        }        
        else if (*it == '{')
        {           
            if((line_state == 1)&&(current.size() > 0))
            {
                diff::blocks::instruction child;            
                child.instr = current;                
                current.clear();

                stack.top()->children.push_back(child);
                stack.push(&stack.top()->children.back());

                line_state = 0;
            }
        }
        else if(*it == '}')
        {
            if(current.size() > 0)
            {
                diff::blocks::instruction child;
                child.instr = current;
                stack.top()->children.push_back(child);
                current.clear();
            }

            stack.pop();
        }
        else if(line_state == 1)
        {
            if(current.size() > 0)
            {
                diff::blocks::instruction child;
                child.instr = current;
                stack.top()->children.push_back(child);
                current.clear();
            }

            current.push_back(*it);
            line_state = 0;
        }
        else current.push_back(*it);

        p = *it;
    }
    
    return result;
}