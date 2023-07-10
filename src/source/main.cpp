#include <iostream>
#include <string.h>
#include "parser.h"
#include "blocks.h"

using namespace std;

int main(int argc, char *argv[])
{  
    diff::parsers::parser p1;
    diff::blocks::block a = p1.load("a.txt");

    diff::parsers::parser p2;
    diff::blocks::block b = p2.load("a_add.txt");

    diff::blocks::block c = a.compare(b);
      
    return 0;
}