#include "Data_Point.h"
#include "unary_e.h"
#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

double const CELL = 10; 
int CELL_COUNT = (int)CELL*CELL;

double x_max, y_max, x_min, y_min; // keeps track of the graph limits
//double xt_max, yt_max, xt_min, yt_min; //its

void x_limit(double& x)
{
    if (x > x_max)
    {
        x_max = x;
    }
    if (x < x_min)
    {
        x_min = x;
    }
}

void y_limit(double& y)
{
    if (y > y_max)
    {
        y_max = y;
    }
    if (y < y_min)
    {
        y_min = y;
    }
}


std::vector<Data_Point> read_tsv(char *fname)
{
    std::ifstream ifs(fname);
    std::vector<Data_Point> items; // Stores the x and y coordinate along with the cell and the perturbed cell of row in the tsv
    int h{}; // tracks the row used to assign x_min /y_min value
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

        while (getline(ss, tmp, '\t'))//loops through each column of the line and picks out long/lat
        {
            if (i == 4)
            {
                x = stod(tmp);
                if (h==0)
                    x_min = x;
                x_limit(x);
            }
            else if (i == 5)
            {
                y = stod(tmp);
                if (h==0)
                    y_min = y;
                y_limit(y);
            }
            i++;
        }
        h++;
        item.set_coord(x, y);
        items.push_back(item);
    }
    return items;
}

void print_map(const VECTWODUB& v, const int& i)
{
    std::cout << "Map cell " << std::setprecision(16) << i << " contents: "<< v[i][0] << ", " << v[i][1] 
            << ", " << v[i][2]<< ", " << v[i][3] << std::endl;
}
    
void print_min_max()
{
    std::cout << "******************************\n";
    std::cout << "X min: " << x_min << " | max: "  << x_max << "\n";
    std::cout << "******************************\n";
    std::cout << "Y min: "<< y_min << " | max: "  <<  y_max << "\n";
    std::cout << "******************************\n";
}

VECTWODUB determine_map()
{
    int cell_count = CELL * CELL;
    VECTWODUB map_cell(cell_count,std::vector<double>(4,0));
    double cell_width = (x_max - x_min)  /(double)CELL;
    double cell_height = (y_max - y_min) /(double)CELL;

    print_min_max();
//    std::cout << cell_count << "\n";
//    std::cout << "Cell width: "<< cell_width << "\nCell Height: "<< cell_height << "\n";

    //Y_max/x_min/ are resetting
    map_cell.at(0) = {y_max, y_max - cell_height, x_min, x_min + cell_width};
//    print_map(map_cell, 0);

    for(int i = 1; i < cell_count; ++i)
    {
        if(i % (int)CELL == 0)
        {
            y_max -= cell_height;
            //std::cout << "y_max is now: "<< std::setprecision(8)<< y_max << "\n\n";
            map_cell.at(i) = {y_max, y_max - cell_height, x_min, x_min + cell_width};
 //           print_map(map_cell, i);
        }
        else
        {
            map_cell.at(i) = {y_max, y_max - cell_height, map_cell[i-1][3], map_cell[i-1][3] + cell_width};
  //          print_map(map_cell, i);
        }
    }
    return map_cell;
}

/* BEGIN Data_Point class*/
void Data_Point::set_coord(double x, double y)
{
    latitude = y;
    longtitude = x;
}

void Data_Point::print_coord()
{
    std::cout << "Location: " << std::setprecision(16) << latitude << ", " << longtitude << std::endl;
}

Data_Point::Data_Point(): perturbed_cell(CELL_COUNT, 0)
{
    latitude = -1.0;
    longtitude = -1.0;
    designated_cell = -1;
}

void Data_Point::set_cell(VECTWODUB vect)//search vect and determine if x,y of user_loation falls in a cells coordinates
{
    FOR(i,0,vect.size())
    {
        if(this->latitude <= vect[i][0] && this->latitude >= vect[i][1])
        {
            if(this->longtitude >= vect[i][2] && this->longtitude <= vect[i][3])
            { 
                this->designated_cell = i + 1;
            }
        }
    }
}

void Data_Point::print_cell()
{
    std::cout << designated_cell;
}

void Data_Point::perturb_cell()
{
    encode(perturbed_cell, CELL_COUNT, designated_cell);
    perturb(perturbed_cell);
}

/*END Data_Point class*/
