#include "population.h"
#include "settings.h"
#include <iostream>
#include <string.h>

using namespace std;

void run()
{
    polymorphic::settings::settings settings;

    settings._children.depth = 3;
    settings._children.max = 5;

    settings._instructions.min = 1;
    settings._instructions.max = 15; 

    settings._loop.min = 1;
    settings._loop.max = 5;

    polymorphic::population p(settings, 2000);

    p.generate();
    polymorphic::schema best = p.go(1000);

    std::cout << best.output();
    std::tuple<std::string, bool, int, int> result = best.run();
    std::cout << std::get<0>(result);
}

#include <future>

bool equality(int a, int b, int desired_num_of_equals)
{
    // n00b basic comparsion
	auto comparison = [](int a, int b) 
	{ 
		return a == b;
	};
	
    int *aa[desired_num_of_equals];
    int *bb[desired_num_of_equals];
    
    // setup parallel arrays
    for (int i = 0; i < desired_num_of_equals; ++i)
    {
        aa[i] = &a;
        bb[i] = &b;
    }

    std::future<bool> results[desired_num_of_equals];

    // compute result in parallel
	for (int i = 0; i < desired_num_of_equals; ++i)
	{
		results[i] = std::async(std::launch::async, comparison, *aa[i], *bb[i]);
	}

    bool result = results[0].get();

    // gather parallel results
    for (int i = 1; i < desired_num_of_equals; ++i)
    {
        result = result && results[i].get();
    }

    return result;
}

int main(int argc, char *argv[])
{  
    // compute;
    // 10 ==================== 10;
    std::cout << equality(10, 10, 20) << std::endl;
    return 0;
}