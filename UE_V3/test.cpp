#include <iostream>
#include <vector>

#include "read_tsv.h"

int main()
{
    std::vector<Data_Point> coordinates = read_tsv((char *)"test.txt");
    REP(i, coordinates.size())
    {
        std::cout << "User: " << i;
        std::cout << "\t";
        coordinates.at(i).print_coord();
        std::cout << std::endl;
    }
    //print_v2d(coordinates);
    //std::cout << 'g';

    return 0;
}