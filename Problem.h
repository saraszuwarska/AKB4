#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

class Problem
{
public:
    std::vector<int> instance;
    Problem()
    {
    }
    Problem(std::string file_name)
    {
        std::ifstream ist(file_name);
        std::string line;

        if (!ist)
            std::cout
                << "Podany plik nie istnieje!\n"
                << std::endl;
        else
        {
            getline(ist, line);
            std::istringstream ist(line);
            this->instance = std::vector<int>(std::istream_iterator<int>(ist), std::istream_iterator<int>());
        }
        printVector(this->instance);
    }

    void printVector(std::vector<int> vector_name)
    {
        for (int i = 0; i < vector_name.size(); i++)
        {
            std::cout << vector_name[i] << " ";
        }
        std::cout << std::endl;
    }

    int map_size()
    {
        int A = this->instance.size();
        int a = 1;
        int b = 3;
        int c = 2 - (2 * A);
        float delta = (b * b) - (4 * a * c);
        float delta_root = sqrt(delta);
        float x1 = ((-b) - delta_root) / 2 * a;
        float x2 = ((-b) + delta_root) / 2 * a;
        std::cout << "delta" << delta << std::endl;
        std::cout << "delta root" << delta_root << std::endl;
        std::cout << "x1" << x1 << std::endl;
        std::cout << "x2" << x2 << std::endl;

        if (delta < 0)
        {
            std::cout << "Delta <0" << std::endl;
            return 0;
        }
        if (delta_root != floor(delta_root))
        {
            std::cout << "Delta root != Floor(Delta root)" << std::endl;
            return 0;
        }
        if ((x1 > 0) || (x2 > 0))
        {
            return fmax(x1, x2);
        }
        return 0;
    }

    std::vector<int> delete_element(std::vector<int> any_vector, int to_delete)
    {
        std::vector<int> new_vector;
        bool removed = false;

        for (int i = 0; i < any_vector.size(); i++)
        {
            if ((any_vector[i] != to_delete) || removed)
            {
                new_vector.push_back(any_vector[i]);
            }
            else
                removed = true;
        }
        return new_vector;
    }

    std::vector<int> delete_multiple(std::vector<int> delete_in, std::vector<int> delete_from)
    {
        std::vector<int> result_vector = delete_in;
        for (int i = 0; i < delete_from.size(); i++)
        {
            result_vector = delete_element(result_vector, delete_from[i]);
        }
        return result_vector;
    }
    int find_max(std::vector<int> any_vector)
    {
        int max_seg = 0;
        for (int i = 0; i < any_vector.size(); i++)
        {
            if (any_vector[i] > max_seg)
            {
                max_seg = any_vector[i];
            }
        }
        return max_seg;
    }
    void first_seg(std::vector<int> &candidates, std::vector<int> &used_elements, std::vector<int> &result_map)
    {
        int max_seg = 0;
        int max2_seg = 0;
        int difference;
        int first_segment;
        max_seg = find_max(candidates);
        difference = max_seg;
        for (int j = 0; j < candidates.size(); j++)
        {
            if (((max_seg - candidates[j]) < difference) && ((max_seg - candidates[j]) > 0))
            {
                difference = max_seg - candidates[j];
                max2_seg = candidates[j];
            }
        }
        first_segment = max_seg - max2_seg;
        std::cout << "Pierwszy element: " << first_segment << std::endl;

        result_map.push_back(first_segment);
        used_elements.push_back(max_seg);
        used_elements.push_back(max2_seg);
        used_elements.push_back(first_segment);
        candidates = delete_multiple(candidates, used_elements);
    }

    void find_solution()
    {
        int k = this->map_size();
        std::cout << "-----" << std::endl;
        std::cout << "K wynosi:" << k << std::endl;
        bool solved = false;
        auto start = std::chrono::high_resolution_clock::now();

        std::cout << "Mapa sklada sie z " << k + 1 << " elementow" << std::endl;
        if (k == 0)
        {
            std::cout << "Podane dane sa nieprawidlowe. Rozwiazanie niemozliwe." << std::endl;
        }
        else
        {
            std::vector<int> candidates;
            std::vector<int> used_elements;
            std::vector<int> result_map;
            candidates = this->instance;
            int max_seg = find_max(candidates);
            first_seg(candidates, used_elements, result_map);
            //printVector(candidates);
            //printVector(used_elements);
            //printVector(result_map);
            algorithm(candidates, used_elements, result_map, solved, max_seg, k, 1);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            if (solved)
            {
                std::cout << "Algorytm potrzebowal " << duration.count() << " milisekund na znalezienie rozwiazania" << std::endl;
            }
            else
                std::cout << "Algorytm dzialal przez " << duration.count() << " milisekund i nie znalazl rozwiazania" << std::endl;
        }
    }

    std::vector<int> cuts(std::vector<int> result_map, int max_seg, int candidate)
    {
        std::vector<int> local_result;
        local_result.push_back(candidate);
        int partial_sum = candidate;
        for (int i = result_map.size() - 1; i >= 0; i--)
        {
            partial_sum += result_map[i];
            local_result.push_back(partial_sum);
        }
        local_result.push_back(max_seg - partial_sum);
        return local_result;
    }
    bool contains(std::vector<int> any_vector, int element)
    {
        for (int i = 0; i < any_vector.size(); i++)
        {
            if (any_vector[i] == element)
            {
                return true;
            }
        }
        return false;
    }
    bool vector_content(std::vector<int> candidates, std::vector<int> possible_candidates)
    {
        for (int i = 0; i < possible_candidates.size(); i++)
        {
            if (!contains(candidates, possible_candidates[i]))
            {
                return false;
            }
        }
        return true;
    }
    std::vector<int> join_vectors(std::vector<int> vector1, std::vector<int> vector2)
    {
        std::vector<int> result_vector = vector1;
        for (int i = 0; i < vector2.size(); i++)
        {
            result_vector.push_back(vector2[i]);
        }
        return result_vector;
    }
    int sum_vector(std::vector<int> any_vector)
    {
        int summed_elements = 0;
        for (int i = 0; i < any_vector.size(); i++)
        {
            summed_elements += any_vector[i];
        }
        return summed_elements;
    }
    void algorithm(std::vector<int> candidates, std::vector<int> used_elements, std::vector<int> result_map, bool &solved, int max_seg, int max_depth, int iteration)
    {
        if (solved)
        {
            return;
        }
        if ((candidates.size() == 0) && (iteration == max_depth) && (result_map.size() == max_depth + 1))
        {
            std::cout << "-- Znaleziono rozwiazanie -- " << std::endl;
            std::cout << "MAPA:" << std::endl;
            printVector(result_map);
            solved = true;
            return;
        }
        if (result_map.size() > max_depth + 1)
        {
            std::cout << "Przekroczono rozmiar mapy" << std::endl;
            return;
        }
        if (candidates.size() == 0)
        {
            std::cout << "Brak elementow do sprawdzenia" << std::endl;
            return;
        }

        for (int i = 0; i < candidates.size(); i++)
        {
            std::vector<int> local_candidates = candidates;
            std::vector<int> local_used_elements = used_elements;
            std::vector<int> local_result_map = result_map;
            std::vector<int> possible_cuts = cuts(local_result_map, max_seg, candidates[i]);
            // std::cout << "Possible cuts dla elementu " << candidates[i] << std::endl;
            //printVector(possible_cuts);
            if (vector_content(candidates, possible_cuts))
            {
                local_result_map.push_back(candidates[i]);
                local_used_elements = join_vectors(local_used_elements, possible_cuts);
                local_candidates = delete_multiple(local_candidates, possible_cuts);
                //std::cout << "Candidates" << std::endl;
                //printVector(local_candidates);
                //std::cout << "Result" << std::endl;
                //printVector(local_result_map);
                //std::cout << "Used" << std::endl;
                //printVector(local_used_elements);
                if (local_candidates.size() == 0)
                {
                    local_result_map.push_back(max_seg - (sum_vector(local_result_map)));
                }
                algorithm(local_candidates, local_used_elements, local_result_map, solved, max_seg, max_depth, iteration + 1);
            }
        }
    }
};

#endif