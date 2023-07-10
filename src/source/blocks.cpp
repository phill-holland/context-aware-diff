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
    
    // instructions
    int idx = 0;
    for(std::vector<std::string>::iterator it = instructions.begin(); it != instructions.end(); ++it)
    {
        //std::string temp = std::to_string(idx) + std::string("_") + *it;
        std::string temp = *it;
        //left[std::tuple<int,std::string>(idx,*it)] = idx;
        if(left.find(temp) != left.end()) left[temp].push_back(idx);
        else left[temp] = { idx };
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
                // does not exist, source is removed
                // or removed
            }
        }
        else 
        {            
            // the line may have changed!!!!! (hello world different!)
            // are surrounding lines the same?

            //t.identifier = std::string("+ ") + temp;
            result.instructions.push_back(std::string("+ ") + temp);
        }

        ++idx;
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
            diff::blocks::block t = *it;
            t.identifier = std::string("+ ") + it->identifier;
            result.children.push_back(t);
        }

        ++idx;
    }

    return result;
}

// children compare -- for functions/procs only, sort functions on both sides
// find new functions (function order not important)