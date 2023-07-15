#include <iostream>
#include <string.h>
#include "parser.h"
#include "parser2.h"
#include "blocks.h"

using namespace std;

int main(int argc, char *argv[])
{  
std::string program = R"(#include <iostream>

using namespace std;

void main()
{
    cout << "hello! \" world!";
    int w = 0;
    for(int a = 10; a < 100; ++a)
    {
        w = w * 2;
        cout << "weeeeee!";
    }
    int c = 145;
})";

    diff::parsers::parser2 p1;
    diff::blocks::instruction i = p1.parse(program);
    //diff::blocks::block a = p1.load("a.txt");

    //diff::parsers::parser p2;
    //diff::blocks::block b = p2.load("a_add.txt");

    //diff::blocks::block c = a.compare(b);
      
    return 0;
}