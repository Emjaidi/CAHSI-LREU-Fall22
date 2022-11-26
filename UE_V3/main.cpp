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
    REP(i,user_location.size())
    {
        user_location.at(i).set_cell(map);
        user_location.at(i).print_coord();
        user_location.at(i).print_cell();
    }
    return 0;
}
