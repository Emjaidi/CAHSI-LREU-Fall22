/*************************************************************
 * 
 * Unary encoding implementation file 
 * AUTHOR: MJ ASUNCION
 * DATE: 12-1-2022
 * 
 * 
 * 
*************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <cmath>/*exp(eulers number), log*/

#include "Data_Point.h"

const int POPULATION = 100;
const std::vector<int> FAV_NUM{1, 2, 3, 4};
//, 5, 6, 7, 8, 9, 10
const float EPSILON = log(3);
const float P = exp(EPSILON/2)/(1 + exp(EPSILON/2));
const float Q = 1.00 - P;

//Function returns vector of bools
//A simulation of bits with the only 1 being the response index in FAV_NUM
std::vector<bool> encode(const int& response)
{
    std::vector<bool> encoded(FAV_NUM.size());
    
    for (int i = 0; i < FAV_NUM.size(); i++)
    {
        if (i + 1 == response)
        {
            encoded[i] = 1;
        }
        else
        {
            encoded[i] = 0;
        }
    }
    return encoded;
}

float coin_flip()
{
    float probability = rand() % 100 + 1;
    float result = probability/100;
    return result;
}

bool perturb_bit(bool bit)
{
    float toss{ };
    //if bit is 1
    if (bit == 1)
    {
        toss = coin_flip();
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
        toss = coin_flip();
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
std::vector<bool> perturb(const std::vector<bool>& e_response)
{
    std::vector<bool> p_response = e_response;
    for(int i= 0; i < e_response.size(); i++)
    {
        p_response.at(i) = perturb_bit(e_response.at(i));
    }
    return p_response;
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