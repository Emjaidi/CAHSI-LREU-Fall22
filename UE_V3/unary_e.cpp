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
#include <random>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time for randomization*/
#include <cmath>/*exp(eulers number), log*/

#include "unary_e.h"

extern int CELL_COUNT;

const int POPULATION = 10000;
const double EPSILON = log(3);
const double P = 0.95;
//exp(EPSILON/2)/(1 + exp(EPSILON/2));
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
    float estimation = (sum - POPULATION * Q)/(2 * P - 1);
    if(estimation < 0){
        return 0;
    }
    else
        return estimation;
}

void populate_sum(const std::vector<Data_Point>& point, std::vector<int>& sum_of_choices)
{
    REP (i, point.size())
    {
        int x {};
        for (auto y: point.at(i).original_cell)
        {
            if (y == 1)
                sum_of_choices.at(x) += 1;

            x++;
        }
    }
}

void populate_perturbed_sum(const std::vector<Data_Point>& point, std::vector<int>& sum_of_choices)
{
    REP (i, point.size())
    {
        int x {};
        for (auto y: point.at(i).perturbed_cell)
        {
            if (y == 1)
                sum_of_choices.at(x) += 1;
            x++;
        }
    }
}

//generates a random double given the parameters x/w

double rand_doub(double fmin, double fmax)
{
/*{ old random doble gen.
    double lower_bound = x;
    double upper_bound = w;
    std::default_random_engine re;
    std::uniform_real_distribution<double> unif(x,w);
    double a_random_double = unif(re);

    return a_random_double;
}*/

    double f = (double)rand() / RAND_MAX;
    return  fmin + f * (fmax - fmin);
}

double haversine(double lat_1, double long_1, double lat_2, double long_2)
{
    auto coord_1 = {lat_1, long_1};
    auto coord_2 = {lat_2, long_2};

    int R = 6371000; //Earth radius in km
    
    auto phi_1 = long_1 * M_PI / 180.0;
    auto phi_2 = long_2 * M_PI / 180.0;

    auto delta_phi = (long_1 - long_2) * M_PI / 180.0;
    auto delta_lambda = (lat_1 - lat_2) * M_PI / 180.0;

    auto a = (pow(sin(delta_phi/2.0), 2)) + cos(phi_1) * cos(phi_2) * (pow(sin(delta_lambda/2.0), 2));

    auto c = 2.0 * atan2(sqrt(a),sqrt(1-a));
    
    return (R * c)/1000.0; 
    }

std::vector<Data_Point> generate_est_map(std::vector<int> choice, VECTWODUB map)
{
    std::vector<Data_Point> est_map;
    REP(i, map.size())
    {
        double w = map[i][0];
        double x = map[i][1];
        double y = map[i][2];
        double z = map[i][3];
        if (choice[i]!=0)
        {
            //loop until k = all the tallied counts at cell choice 
            REP(j,choice[i])
            {
                Data_Point usr;
                usr.set_lat(rand_doub(x,w));
                usr.set_long(rand_doub(z,y));                    
                usr.set_cell(i);
                est_map.push_back(usr);
            }
        }
        /*else
        {
            est_map.push_back()
        }*/
    } 
    return est_map;
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