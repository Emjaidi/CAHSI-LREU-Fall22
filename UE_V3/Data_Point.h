/*
/ Data point class for storing latitude/longitude of user data
/ Unary encoding implementation of LDP
*/

/*******************************
 *          TODO
 *  - [ ] Set cell function
 *      - [ ] Determine how many cells are in graph
 *      - [ ] 
 *  - [ ] perturb cell function 
 *      - [ ] 
 * 
*******************************/

#include<vector>

#ifndef DATA_POINT_H
#define DATA_POINT_H

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define VECTWODUB std::vector<std::vector<double> >

double const CELL = 7; 

class Data_Point
{
    double latitude;//Y-axis
    double longtitude;//X-axis
    int designated_cell;
    int perturbed_cell;
public:
    Data_Point();
    void print_coord();
    void set_coord(double, double);
    void set_cell(VECTWODUB);
    void perturb_cell();
    void print_cell();
};

std::vector<Data_Point> read_tsv(char* file);

void x_limit(double);
void y_limit(double);

VECTWODUB determine_map();
#endif
