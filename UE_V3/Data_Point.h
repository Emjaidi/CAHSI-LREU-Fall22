/*
/ Data point class for storing latitude/longitude of user data
/ Unary encoding implementation of LDP
*/

/*******************************
 *          TODO
 * 
*******************************/

#include<vector>

#ifndef DATA_POINT_H
#define DATA_POINT_H

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define VECTWODUB std::vector<std::vector<double> >
#define VECTWOBOOL std::vector<std::vector<bool> >

class Data_Point
{
public:
    double latitude;//Y-axis
    double longtitude;//X-axis
    int designated_cell;
    std::vector<bool> original_cell;
    std::vector<bool> perturbed_cell;
    Data_Point();
    //std::vector<Data_Point> fab_loc(VECTWODUB, std::vector<int>);
    void set_lat(double);
    void set_long(double);
    void set_cell(int);
    void print_coord();
    void set_coord(double, double);
    void set_cell(VECTWODUB);
    void encode_cell();
    void perturb_cell();
    void print_cell();
};

std::vector<Data_Point> read_tsv(char* file);

void x_limit(double&);
void y_limit(double&);

//std::vector<double> random_coord(double,double,double,double);

std::vector<double> random_coord();

std::vector<int> generate_dp_in_radius(const std::vector<Data_Point>&, const std::vector<Data_Point>&);

VECTWODUB determine_map();
#endif
