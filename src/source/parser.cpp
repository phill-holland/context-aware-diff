#include "parser.h"
#include <fstream>
#include <iostream>

using namespace std;

diff::blocks::block diff::parsers::parser::load(std::string filename)
{
    diff::blocks::block result;

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

diff::blocks::block diff::parsers::parser::parse(std::string data)
{
    // load lines into instructions, until { is reached
    // look for line before { to get "block identifier", i.e. class name, function name    
}