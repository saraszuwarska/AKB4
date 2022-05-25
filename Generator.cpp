#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <time.h>

void printVector(std::vector<int> vector_name)
{
    for (int i = 0; i < vector_name.size(); i++)
    {
        std::cout << vector_name[i] << " ";
    }
    std::cout << std::endl;
}
std::vector<int> cuts_generator(std::vector<int> map)
{
    std::vector<int> full_map = map;
    for (int i = 0; i < map.size(); i++)
    {
        int sum = map[i];
        for (int j = i + 1; j < map.size(); j++)
        {
            sum += map[j];
            full_map.push_back(sum);
        }
    }
    return full_map;
}

void save_File(std::string file_name, std::vector<int> generated_map)
{
    std::ofstream outfile;
    outfile.open(file_name);

    std::cout << "ZAPISANO PLIK" << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < generated_map.size(); i++)
    {
        outfile << generated_map[i] << " ";
    }
    outfile.close();
}
bool desc(int a, int b)
{
    return a > b;
}
bool asc(int a, int b)
{
    return a < b;
}

int main()
{
    std::srand(time(NULL));
    for (int i = 5; i <= 14; i += 3)
    {
        std::string fileASC = std::to_string(i) + "GeneratedMapASC.txt";
        std::string fileDSC = std::to_string(i) + "GeneratedMapDSC.txt";
        std::vector<int> map;
        std::vector<int> map2;
        std::vector<int> cutsASC;
        std::vector<int> cutsDSC;
        for (int j = 0; j < i; j++)
        {
            map.push_back(rand() % 18 + 2);
        }
        for (int k = 0; k < i; k++)
        {
            map2.push_back(rand() % 18 + 2);
        }
        cutsASC = cuts_generator(map);
        std::sort(cutsASC.begin(), cutsASC.end());
        std::cout << "MAPA" << std::endl;
        printVector(map);
        std::cout << "---------------" << std::endl;
        printVector(cutsASC);
        std::cout << "---------------" << std::endl;
        save_File(fileASC, cutsASC);

        cutsDSC = cuts_generator(map2);
        std::sort(cutsDSC.begin(), cutsDSC.end());
        std::reverse(cutsDSC.begin(), cutsDSC.end());
        save_File(fileDSC, cutsDSC);
        std::cout << "MAPA" << std::endl;
        printVector(map2);
        std::cout << "---------------" << std::endl;
        printVector(cutsDSC);
        std::cout << "---------------" << std::endl;
    }
}