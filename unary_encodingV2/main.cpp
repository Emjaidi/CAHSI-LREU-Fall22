/******************************************************************************
Author:
    MJ Asuncion
Date Composed:
    <2022-11-04 Fri>
Description:
    Program that implements the Unary encoding protocol of LDP

*******************************************************************************/
    /*---------TODO-------------
    * - [x] Generate population
    * -     - Each with own response
    *       - [x] Populate a vector with index as individual and the
    *            choice (1-10) indexes their FAV_COLOR
    *       - [ ]
    * - [x] Perturb the responses
    *       - [ ]
    * - [x] aggregate/estimate the responses
    *       - [ ]
     - [x] output the real numbers gathered
    --------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <cmath>/*exp(eulers number), log*/

using namespace std;

const int POPULATION = 100;
const vector<int> FAV_NUM{1, 2, 3, 4};
//, 5, 6, 7, 8, 9, 10
const float EPSILON = log(3);
const float P = exp(EPSILON/2)/(1 + exp(EPSILON/2));
const float Q = 1.00 - P;

//Function returns vector of bools
//A simulation of bits with the only 1 being the response index in FAV_NUM
vector<bool> encode(const int& response)
{
    vector<bool> encoded(FAV_NUM.size());
    
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

int person_fav()
{
    return rand()% FAV_NUM.size() + 1;
}

void populate_individuals(vector<vector<int> >& ind)
{
    for (int x = 0; x < ind.size(); x++)
    {
        for (int i = 0; i < 1; i++)
        {
            ind.at(x).push_back(person_fav());
        }
    }
}

//perturb each bit of the vector
vector<bool> perturb(const vector<bool>& e_response)
{
    vector<bool> p_response = e_response;
    for(int i= 0; i < e_response.size(); i++)
    {
        p_response.at(i) = perturb_bit(e_response.at(i));
    }
    return p_response;
}

template <typename T>
void print_response(const vector<vector<T> >& response)
{
    for (auto x: response)
    {
        for (auto y:x)
        {
            cout<< y << " ";
        }
        cout << endl;
    }
}

//Transpose the perturbed response vector to tally up the sum of choices
vector<vector<bool> > transpose_response(const vector<vector<bool> >& response)
{
    vector<vector<bool> > transposed_response(response[0].size(), vector<bool>());
    for (int i = 0; i < response.size(); i++)
    {
        for (int j = 0; j < response[i].size(); j++)
        {
            transposed_response[j].push_back(response[i][j]);
        }
    }
    return transposed_response;
}


void populate_sum(const vector<vector<bool> >& og_transposed_response, vector<int>& og_sum_of_choices)
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

float estimate(const int& sum)
{
    float estimation = sum - POPULATION * Q/2 * P - 1;
    return estimation;
}


int main()
{
    vector<vector<int> > individuals(POPULATION, vector<int> ());//Keeps track of individuals and their favorite color;
    vector<vector<bool> > encoded_response(POPULATION,vector<bool>());//Keeps track of the encoded response of the individuals;
    vector<vector<bool> > perturbed_response(POPULATION,vector<bool>());//Keeps track of the perturbed response of the individuals;
    vector<int> og_sum_of_choices(FAV_NUM.size());//Used for the tally in the original choices
    vector<int> sum_of_choices(FAV_NUM.size());//Used for the sum in the estimation formula
    
    /*init random seed*/
    srand(time(NULL));
    
    populate_individuals(individuals);
    
    /*
    cout << "Here are everyones favorite number: \n";
    print_response(individuals);
    */
    
    //encode_responses of the population
    for(int i = 0; i < individuals.size(); i++)
    {
        for(int x = 0; x < individuals.at(i).size(); x++)
        {
            encoded_response.at(i) = encode(individuals[i][x]);
        }
    }
    

    //Perturb the responses
    for (int i = 0; i < encoded_response.size(); i++)
    {
        perturbed_response.at(i) = perturb(encoded_response[i]);
    }
    
    //print out the encoded_response
    /*
    cout << "Here are the encoded responses: \n";
    print_response(encoded_response);
    */

    
    /*
    cout << "Here are the perturbed responses: \n";
    print_response(perturbed_response);
    */
    
    //Aggregate/estimate the data']]
    //Transpose the matrices
    vector<vector<bool> > og_transposed_response = transpose_response(encoded_response);
    vector<vector<bool> > transposed_response = transpose_response(perturbed_response);
    
    populate_sum(og_transposed_response, og_sum_of_choices);
    populate_sum(transposed_response, sum_of_choices);

    //Populate the sum_of_choices
    
    
    cout << "\nHere is the tally of the original choices: \n";
    for (auto x: og_sum_of_choices)
        cout << x << " ";
    cout << endl;
    
    cout << "\nHere is the tally of the perturbed choices: \n";
    for (auto x: sum_of_choices)
        cout << x << " ";
    cout << endl;
    
    cout << "Favorite Number\t Estimation\n";
    for (int i = 0; i < sum_of_choices.size(); i++)
    {
        cout << i + 1 << "\t\t\t\t\t" << estimate(sum_of_choices[i]);
        cout << endl;
    }
    
    return 0;
}

