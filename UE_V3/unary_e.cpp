/*************************************************************
 * 
 * Unary encoding implementation file 
 * AUTHOR: MJ ASUNCION
 * DATE: 12-1-2022
 * 
*************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time for randomization*/
#include <cmath>/*exp(eulers number), log*/

#include "unary_e.h"

const int POPULATION = 100;
//const std::vector<int> FAV_NUM{1, 2, 3, 4};
//, 5, 6, 7, 8, 9, 10
const double EPSILON = log(3);
const double P = exp(EPSILON/2)/(1 + exp(EPSILON/2));
const double Q = 1.00 - P;

//Function returns vector of bools
//A simulation of bits with the only 1 being the response index in FAV_NUM
void encode(std::vector<bool>& response, int cell_count, int cell)
{
    for (int i = 0; i < cell_count; i++)
    {
        if (i + 1 == cell)
        {
            response[i] = 1;
        }
        else
        {
            response[i] = 0;
        }
    }
}

double coins_flip()
{
    double probability = rand() % 100 + 1;
    double result = probability/(double)100;
    return result;
}

bool perturb_bit(bool bit)
{
    double toss{ };
    //if bit is 1
    if (bit == 1)
    {
        toss = coins_flip();
        if (toss <= P)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        toss = coins_flip();
        if (toss <= Q)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

//perturb each bit of the vector
void perturb(std::vector<bool>& e_response)
{
    for(int i= 0; i < e_response.size(); i++)
    {
        e_response.at(i) = perturb_bit(e_response.at(i));
    }
}

float estimate(const int& sum)
{
    float estimation = sum - POPULATION * Q/2 * P - 1;
    return estimation;
}

void populate_sum(const VECTWOBOOL& og_transposed_response, std::vector<int>& og_sum_of_choices)
{
    for (int x = 0; x < og_transposed_response.size(); x++)
    {
        for (auto y: og_transposed_response.at(x))
        {
            if (y == 1)
                og_sum_of_choices.at(x) += 1;
        }
    }
}

//Transpose the perturbed response vector to tally up the sum of choices
VECTWOBOOL transpose_response(const VECTWOBOOL& response)
{
    VECTWOBOOL transposed_response(response[0].size(), std::vector<bool>());
    for (int i = 0; i < response.size(); i++)
    {
        for (int j = 0; j < response[i].size(); j++)
        {
            transposed_response[j].push_back(response[i][j]);
        }
    }
    return transposed_response;
}