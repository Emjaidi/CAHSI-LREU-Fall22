#include "Data_Point.h"
#include <iostream>
#include <iomanip>
/* BEGIN Data_Point class*/


void Data_Point::set_coord(double x, double y)
{
    latitude = x;
    longtitude = y;
}

void Data_Point::print_coord()
{
    std::cout << "Location: " << std::setprecision(16) << latitude << ", " << longtitude << std::endl;
}
/*END Data_Point class*/