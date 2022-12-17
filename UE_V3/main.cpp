/***
 * 
 *  read_tsv.h
 *  unary_encodingV2
 *  Created by MJ Asuncion on 11/19/22.
 * */
#include "Data_Point.h"
#include "unary_e.h"
#include <vector>
#include <iostream>

extern int CELL_COUNT;

int main()
{
    std::vector<Data_Point> user_location = read_tsv((char *)"exp.txt");
    std::vector<Data_Point> est_user_location;
    VECTWODUB map = determine_map();
    std::vector<int> og_sum_of_choices(CELL_COUNT,0);
    std::vector<int> sum_of_choices(CELL_COUNT,0);
    std::vector<int> est_choices(CELL_COUNT,0);

    REP(i,user_location.size())
    {
        user_location.at(i).set_cell(map);
        //std::cout << "Data point " << i << " is located in cell: ";
        //user_location.at(i).print_cell();
        user_location.at(i).encode_cell();
        //std::cout << "\n";
        /*
        for(auto j: user_location[i].original_cell)
        {
            std::cout << j << " ";
        }*/
        user_location.at(i).perturbed_cell = user_location.at(i).original_cell;
        user_location.at(i).perturb_cell();
        //std::cout << "\nCELL PERTURBED*****************\n";
        
        /*for(auto j: user_location[i].perturbed_cell)
        {
            std::cout << j << " ";
        }
        std::cout << "\n******************************\n";
        */
       // std::cout << "Its coordinate ";
       // user_location.at(i).print_coord();
       // std::cout << "\n";
    }

    populate_sum(user_location,og_sum_of_choices);
    populate_perturbed_sum(user_location,sum_of_choices);

    //populate the estimated choices vect
    REP(i, sum_of_choices.size())
    {
        est_choices.at(i) = (int)estimate(sum_of_choices.at(i));
    }
    /*REP(i,est_choices.size())
    {
        est_user_location.at(i).e
    }*/

    printf("Here is the tally of the unperturbed choices:\n");

    for(auto x:og_sum_of_choices)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    printf("Here is the tally of the perturbed choices:\n");
    for(auto x:sum_of_choices)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    printf("Here is the estimation of the choices:\n");
    for(auto i:est_choices)
    {
        std::cout << i << " ";
    }
    //std::cout << "Cell location\t\t\t\tEstimation\n";
//    for (int i = 0; i < sum_of_choices.size(); i++)
//    {
//        std::cout << i + 1 << "\t\t\t\t\t" << estimate(sum_of_choices[i]) << "\t\t\t\t\t";
//        std::cout << std::endl;
//    }


    return 0;
}
