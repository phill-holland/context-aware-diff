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

/*
    std::unordered_map<std::string,std::vector<int>> left;
    std::unordered_map<int,std::string> left_lines;


    int idx = 0;
    for(std::vector<std::string>::iterator it = instructions.begin(); it != instructions.end(); ++it)
    {
        std::string temp = *it;     
        if(left.find(temp) != left.end()) left[temp].push_back(idx);
        else left[temp] = { idx };
        // ***
        left_lines[idx] = temp;

        ++idx;
    }

    idx = 0;
    for(std::vector<std::string>::iterator it = source.instructions.begin(); it != source.instructions.end(); ++it)
    {
        std::string temp = *it;
        if(left.find(temp) != left.end())
        {
            if(*left[temp].begin()==idx)
            {
                result.instructions.push_back(temp);
            }
            else 
            {
            }

            int t = left[temp].front();
            if(t != idx) 
            {
                std::string out = std::string("") + temp + std::string("\n");
                result.instructions.push_back(out);
            }

            left[temp] = { };
        }
        else 
        {            
            std::string out = std::string("+ ") + temp + std::string("\n");

            result.instructions.push_back(out);//std::string("+ ") + temp);
        }

        ++idx;
    }
    
    for(auto &it:left)
    {
        if(it.second.size() > 0)
        {
            std::string out = std::string("- ") + it.first + std::string("\n");
            result.instructions.emplace(result.instructions.begin() + it.second.front(),out);
        }
    }
    */

// ****
    std::unordered_map<std::string,std::vector<int>> right;
    
    // instructions
    int idx = 0;
    for(std::vector<diff::blocks::instruction>::iterator it = children.begin(); it != children.end(); ++it)
    {
        //std::string temp = std::to_string(idx) + std::string("_") + *it;
        std::string temp = it->instr;
        //left[std::tuple<int,std::string>(idx,*it)] = idx;
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
                result.children.push_back(t);//it->compare(children[idx]));
            }
            else 
            {
                // does not exist, source is removed
                // or removed
            }

            int t = right[temp].front();
            if(t != idx) 
            {
                diff::blocks::instruction ttt;
                ttt.instr = std::string("") + temp + std::string("\n");
                result.children.push_back(ttt);
            }

            right[temp] = { };
        }
        else 
        {
            /*
            diff::blocks::block t = *it;
            t.identifier = std::string("+ ") + it->identifier;
            result.children.push_back(t);
            */
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
            //std::string out = std::string("- ") + it.first + std::string("\n");
            //result.children.emplace(result.children.begin() + it.second.front(),it.prefix("- "));
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

// children compare -- for functions/procs only, sort functions on both sides
// find new functions (function order not important)

