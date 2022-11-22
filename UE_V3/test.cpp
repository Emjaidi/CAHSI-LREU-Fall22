#include <iostream>
#include <vector>

#include "read_tsv.h"

//std::vector<std::vector<int> > items; //Stores the x and y coordinate of row in the tsv
//#define VECTWODUB std::vector<std::vector< long double> > 

int main(){
    VECTWODUB coordinates = read_tsv((char *)"test.txt");
    print_v2d(coordinates);
    return 0;
}