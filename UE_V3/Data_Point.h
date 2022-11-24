/*
/ Data point class for storing latitude/longitude of user data
/ Unary encoding implementation of LDP
/
*/
#ifndef DATA_POINT_H
#define DATA_POINT_H

class Data_Point
{
    double latitude = -1.0;
    double longtitude = -1.0;
    int cell = -1;
    int perturbed_cell = -1;

public:
    void print_coord();
    void set_coord(double, double);
    void set_cell(double, double);
    void perturb_cell();
};
#endif