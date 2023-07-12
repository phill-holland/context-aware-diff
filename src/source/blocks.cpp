#include "blocks.h"
#include <unordered_map>
#include <tuple>

void diff::blocks::block::clear()
{
    identifier.clear();
    instructions.clear();
    children.clear();
}

diff::blocks::block diff::blocks::block::compare(block source)
{
    diff::blocks::block result;

    // for each instrsuction in source
    // find it's position in current instruction
    // is it in same position?
    // if not
    // insert or delete happened
    // are instructions after that one in source, in current
    // still in correct order after?
/*
// MOVE TO CHILDREN LOOP
    if(identifier.compare(source.identifier)==0) result.identifier = identifier;
    else 
    {
        result.identifier = std::string("- ") + identifier;
        result.identifier += std::string("+ ") + source.identifier + std::string("\r\n");
    }
*/
    //std::unordered_map<std::tuple<int,std::string>, int> left;//, right;
    std::unordered_map<std::string,std::vector<int>> left;
    std::unordered_map<int,std::string> left_lines;
    // instructions
    int idx = 0;
    for(std::vector<std::string>::iterator it = instructions.begin(); it != instructions.end(); ++it)
    {
        //std::string temp = std::to_string(idx) + std::string("_") + *it;
        std::string temp = *it;
        //left[std::tuple<int,std::string>(idx,*it)] = idx;
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
                //std::string out = std::string("+ ") + temp + std::string("\n");
                //result.instructions.push_back(out);
                // does not exist, source is removed
                // or removed
            }

            left[temp] = { };
        }
        else 
        {            
            // the line may have changed!!!!! (hello world different!)
            // are surrounding lines the same?
            //t.identifier = std::string("+ ") + temp;
            // find by line_number in left!
            std::string out = std::string("+ ") + temp + std::string("\n");
            /*if(left_lines.find(idx) != left_lines.end())
            {
                out += std::string("- ") + left_lines[idx] + std::string("\n");
            }*/
            //out += std::string("+ ") + source.identifier + std::string("\r\n");

            result.instructions.push_back(out);//std::string("+ ") + temp);
        }

        /*
        if(left_lines.find(idx) != left_lines.end())
        {
            std::string tt = left_lines[idx];
            if(tt != temp)
            {
                std::string out = std::string("+ ") + temp + std::string("\n");
                result.instructions.push_back(out);
            }
        }
        */

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
    // loop through left hash, anything left over is added

// ****
    std::unordered_map<std::string,std::vector<int>> right;
    
    // instructions
    idx = 0;
    for(std::vector<diff::blocks::block>::iterator it = children.begin(); it != children.end(); ++it)
    {
        //std::string temp = std::to_string(idx) + std::string("_") + *it;
        std::string temp = it->identifier;
        //left[std::tuple<int,std::string>(idx,*it)] = idx;
        if(right.find(temp) != right.end()) right[temp].push_back(idx);
        else right[temp] = { idx };
        ++idx;
    }


    idx = 0;
    for(std::vector<diff::blocks::block>::iterator it = source.children.begin(); it != source.children.end(); ++it)
    {
        //result.children.push_back(it->compare(
        //std::string temp = std::to_string(idx) + std::string("_") + *it;
        //if(left.find(temp) != left.end())
        //{

        //}
        //++idx;
        //children.push_back(
        std::string temp = it->identifier;
        if(right.find(temp) != right.end())
        {
            if(*right[temp].begin()==idx)
            {
                diff::blocks::block t = children[idx].compare(*it);
                t.identifier = temp;
                result.children.push_back(t);//it->compare(children[idx]));
            }
            else 
            {
                // does not exist, source is removed
                // or removed
            }
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

    return result;
}

diff::blocks::block diff::blocks::block::prefix(std::string value)
{
    diff::blocks::block result;

    result.identifier = value + identifier;

    for(std::vector<std::string>::iterator it = instructions.begin(); it != instructions.end(); ++it)
    {
        result.instructions.push_back(value + *it);
    }

    for(std::vector<diff::blocks::block>::iterator it = children.begin(); it != children.end(); ++it)
    {
        result.children.push_back(it->prefix(value));
    }

    return result;
}

void diff::blocks::block::save(std::string filename)
{
}

std::string diff::blocks::block::output()
{
    std::string result;

    if(identifier.size() > 0) 
    {
        result += identifier + std::string("\n");
        result += std::string("{") + std::string("\n");
    }

    for(std::vector<std::string>::iterator it = instructions.begin(); it != instructions.end(); ++it)
    {
        result += *it + std::string("\n");
    }

    for(std::vector<diff::blocks::block>::iterator it = children.begin(); it != children.end(); ++it)
    {
        result += it->output();
    }

    if(identifier.size() > 0) 
    {
        result += std::string("}") + std::string("\n");
    }

    return result;
}

// children compare -- for functions/procs only, sort functions on both sides
// find new functions (function order not important)

