#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Problem.h"

std::string file = "Example.txt";
std::string generated_file = "11GeneratedMapDSC.txt";
int main()
{

    Problem new_problem(file);
    std::cout << new_problem.map_size() << std::endl;
    new_problem.find_solution();
}