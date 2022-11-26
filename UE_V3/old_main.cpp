/******************************************************************************
Author:
    MJ Asuncion
Date Composed:
    <2022-11-04 Fri>
Description:
    Program that implements the Unary encoding protocol of LDP

*******************************************************************************/
    /*---------TODO-------------
    *   
   
    --------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */


#include "read_tsv.h"
#include "unary_encoding.h"

using namespace std;



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

template <typename T>
void print_response(const vector<vector<T> >& response)
{
    for (auto x: response)
    {
        for (auto y:x)
        {
            cout<< y << " ";
        }
        // cout << endl;
    }
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
    
    //Aggregate/estimate the data']]
    //Transpose the matrices
    vector<vector<bool> > og_transposed_response = transpose_response(encoded_response);
    vector<vector<bool> > transposed_response = transpose_response(perturbed_response);
    
    populate_sum(og_transposed_response, og_sum_of_choices);
    populate_sum(transposed_response, sum_of_choices);
    
    /*
     For loop above and below should be made into its function
     */
    
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
        cout << i + 1 << "\t\t" << estimate(sum_of_choices[i]);
        cout << endl;
    }
    
    return 0;
}

