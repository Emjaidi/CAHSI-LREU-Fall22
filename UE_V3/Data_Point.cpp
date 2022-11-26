#include "Data_Point.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>


double x_max, y_max, x_min, y_min; // keeps track of the graph limits

void x_limit(double x)
{
    if (x > x_min)
    {
        if (x > x_max)
        {
            x_max = x;
        }
    }
    if (x < x_max)
    {
        if (x > x_min)
        {
            x_min = x;
        }
    }
}

void y_limit(double y)
{
    if (y > y_min)
    {
        if (y > y_max)
        {
            y_max = y;
        }
    }
    if (y < y_max)
    {
        if (y > y_min)
        {
            y_min = y;
        }
    }
}


std::vector<Data_Point> read_tsv(char *fname)
{
    std::ifstream ifs(fname);
    std::vector<Data_Point> items; // Stores the x and y coordinate along with the cell and the perturbed cell of row in the tsv

    if (ifs.fail())
    { // incase stream fails
        Data_Point item;
        std::vector<Data_Point> err(1, item);
        std::cerr << "error" << std::endl;
        return err;
    }
    std::string line;
    while (getline(ifs, line))
    { // as long as there is input from line
        std::stringstream ss(line);
        Data_Point item; // stores the columns in the row
        std::string tmp;
        int i{}; // keeps track of the column index
        double x{};
        double y{};

        while (getline(ss, tmp, '\t'))
        {
            if (i == 4)
            {
                x = stod(tmp);
                // std::cout << x << std::endl;
                x_limit(x);
            }
            else if (i == 5)
            {
                y = stod(tmp);
                // std::cout << y << std::endl;
                y_limit(y);
            }
            i++;
        }

        item.set_coord(x, y);
        items.push_back(item);
    }
    return items;
}


VECTWODUB determine_map()
{
    int CELL_COUNT = CELL * CELL;
    VECTWODUB map_cell(CELL_COUNT,std::vector<double>(4,0));
    double cell_width = (x_max - x_min) * (1/CELL);
    double cell_height = (y_max - y_min) * (1/CELL);
    std::cout << CELL_COUNT << "\n";

    map_cell.at(0) = {y_max, y_max - cell_height, x_min, x_min + cell_width};
    for(int i = 1; i < CELL_COUNT; ++i)
    {
        map_cell.at(i) = {y_max, y_max - cell_height, map_cell[i-1][3], map_cell[i-1][2] + cell_width};
        if(i % (int)CELL == 0)
        {
            y_max -= cell_height;
            std::cout << y_max << "\n";
        }
    }
    return map_cell;
}

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

Data_Point::Data_Point()
{
    latitude = -1.0;
    longtitude = -1.0;
    designated_cell = -1;
    perturbed_cell = -1;
}

void Data_Point::set_cell(VECTWODUB vect)//search vect and determine if x,y of user_loation falls in a cells coordinates
{
    REP(i,vect.size())
    {
        if(this->latitude <= vect[i][0])
        {
            if(this->longtitude >= vect[i][2]) 
            {
                if(this->latitude > vect[i][1])
                { 
                    if(this->longtitude < vect[i][3])
                    {
                        this->designated_cell = i;
                    }
                }
            }
        }
    }
}

//void Data_Point::set_cell(VECTWODUB vect)//search vect and determine if x,y of user_loation falls in a cells coordinates
//{
//    REP(i,vect.size())
//    {
//        if(this->latitude <= vect[i][0] && this->longtitude >= vect[i][2] && this->latitude > vect[i][1] && this->longtitude < vect[i][3])
//        {
//            this->designated_cell = i;
//        }
//    }
//}
//
void Data_Point::print_cell()
{
    std::cout << designated_cell;
}
/*END Data_Point class*/
