//
//  read_tsv.h
//  unary_encodingV2
//
//  Created by MJ Asuncion on 11/19/22.
//
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define VECTWOINT std::vector<std::vector<double> > 


#ifndef read_tsv_h
#define read_tsv_h

VECTWOINT items; //Stores the x and y coordinate of row in the tsv

double max_x, max_y, min_x, min_y; //keeps track of the graph limits

void read_tsv(char* fname) {
    std::ifstream ifs(fname);
    
    if (ifs.fail()) { //incase stream fails
        std::cerr << "error" << std::endl;
        return;
    }
    std::string line;
    while (getline(ifs, line)) { //as long as there is input from line
        std::stringstream ss(line);
        std::vector<int> item;//stores the columns in the row
        std::string tmp;
        int i = 0;
        while(getline(ss, tmp, '\t')) {
            if(i == 4 || i == 5){
                item.push_back(stod(tmp));
            }
            i++;
        }
        items.push_back(item);
    }
    REP(i,items.size()) {
        REP(j, items[i].size())
            std::cout << "[" << i << "][" << j <<"]: " << items[i][j] << std::endl;
    }
    return;
}

void grap_limit_x(int i)


#endif /* read_tsv_h */
