/***
 * 
 *  read_tsv.h
 *  unary_encodingV2
 *  Created by MJ Asuncion on 11/19/22.
 * */
#include "Data_Point.h"
#include <vector>
#include <iostream>

int main()
{
    std::vector<Data_Point> user_location = read_tsv((char *)"test.txt");
    VECTWODUB map = determine_map();
    FOR(i,0,user_location.size())
    {
        user_location.at(i).set_cell(map);
        for(auto j: user_location[i].perturbed_cell)
        {
            std::cout << j << " ";
        }
        
        user_location.at(i).perturb_cell();
        std::cout << "\n";
        std::cout << "Data point " << i << " is located in cell: ";
        user_location.at(i).print_cell();
        std::cout << "\n*************CELL PERTURBED*****************\n";
        
        for(auto j: user_location[i].perturbed_cell)
        {
            std::cout << j << " ";
        }
        std::cout << "\n******************************\n";
       // std::cout << "Its coordinate ";
       // user_location.at(i).print_coord();
       // std::cout << "\n";

    }
    return 0;
}
