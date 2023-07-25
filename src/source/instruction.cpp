#include "instruction.h"
#include <unordered_map>
#include <tuple>
#include <fstream>
#include <iostream>

void diff::blocks::instruction::clear()
{
    instr.clear();    
    children.clear();
}

diff::blocks::instruction diff::blocks::instruction::compare(instruction source)
{
    diff::blocks::instruction result;

    std::unordered_map<std::string,std::vector<int>> right;
    
    int idx = 0;
    for(std::vector<diff::blocks::instruction>::iterator it = children.begin(); it != children.end(); ++it)
    {
        std::string temp = it->instr;

        if(right.find(temp) != right.end()) right[temp].push_back(idx);
        else right[temp] = { idx };
        ++idx;
    }

    idx = 0;
    for(std::vector<diff::blocks::instruction>::iterator it = source.children.begin(); it != source.children.end(); ++it)
    {
        std::string temp = it->instr;
        if(right.find(temp) != right.end())
        {
            if(*right[temp].begin()==idx)
            {
                diff::blocks::instruction t = children[idx].compare(*it);
                t.instr = temp;
                result.children.push_back(t);
            }
            else 
            {
            }

            int t = right[temp].front();
            if(t != idx) 
            {
                diff::blocks::instruction ttt;
                ttt.instr = std::string("") + temp;
                result.children.push_back(ttt);
            }

            right[temp] = { };
        }
        else 
        {
           result.children.push_back(it->prefix(std::string("+ ")));
        }

        ++idx;
    }

    for(auto &it:right)
    {
        if(it.second.size() > 0)
        {
            diff::blocks::instruction tt = children[it.second.front()].prefix(std::string("- "));
            result.children.emplace(result.children.begin() + it.second.front(),tt);
        }
    }

    return result;
}

diff::blocks::instruction diff::blocks::instruction::prefix(std::string value)
{
    diff::blocks::instruction result;

    result.instr = value + instr;

    for(std::vector<diff::blocks::instruction>::iterator it = children.begin(); it != children.end(); ++it)
    {
        result.children.push_back(it->prefix(value));
    }

    return result;
}

void diff::blocks::instruction::save(std::string filename)
{
    std::ofstream source(filename, std::ios::out | std::ios::binary);
    if(!source) return;

    std::string data = output();
    if(data.size() <= 0) return;

    source.write(data.c_str(), data.size());

    source.close();
}

std::string diff::blocks::instruction::output()
{
    std::string result;
    std::string prefix;

    if(instr.size() > 0)
    {
        if(instr.size() > 1)
        {
            if(instr[0] == '-') prefix = "- ";
            else if(instr[0] == '+') prefix = "+ ";
        }

        result += instr + std::string("\n");

        if(children.size() > 0)
        {
            result += prefix + std::string("{") + std::string("\n");
        }
    }

    for(std::vector<diff::blocks::instruction>::iterator it = children.begin(); it != children.end(); ++it)
    {
        result += it->output();
    }

    if ((children.size() > 0)&&(instr.size() > 0))
    {
        result += prefix + std::string("}") + std::string("\n");
    }

    return result;
}
