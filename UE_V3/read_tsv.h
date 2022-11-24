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
#define VECTWODUB std::vector<std::vector<double> >

#ifndef read_tsv_h
#define read_tsv_h

/* BEGIN Data_Point class*/
class Data_Point
{
    double latitude = -1.0;
    double longtitude = -1.0;;
    int cell = -1;
    int perturbed_cell = -1;
public:
    void print_coord();
    void set_coord(double, double);
    void set_cell(double, double);
    void perturb_cell();
};

void Data_Point::set_coord(double x, double y)
{
    latitude = x;
    longtitude = y;
}

void Data_Point::print_coord()
{
    std::cout << "Location: " << std::setprecision(16) << latitude << ", "  << longtitude << std::endl;
}
/*END Data_Point class*/

double max_x{}, max_y{}, min_x{}, min_y{}; //keeps track of the graph limits

void x_limit(double x)
{
    if (x > min_x)
    {
        if(x > max_x)
        {
            max_x = x;
        }
    }
    if (x < max_x)
    {
        if(x > min_x)
        {
            min_x = x;
        }
    }
}

void y_limit(double y)
{
    if (y > min_y)
    {
        if(y > max_y)
        {
            max_y = y;
        }
    }
    if (y < max_y)
    {
        if(y > min_y)
        {
            min_y = y;
        }
    }
}
std::vector<Data_Point> read_tsv(char* fname) {
    std::ifstream ifs(fname);
    std::vector<Data_Point> items; //Stores the x and y coordinate along with the cell and the perturbed cell of row in the tsv
    
    if (ifs.fail()) { //incase stream fails
        Data_Point item;
        std::vector<Data_Point> err(1,item);
        std::cerr << "error" << std::endl;
        return err;
    }
    std::string line;
    while (getline(ifs, line)) { //as long as there is input from line
        std::stringstream ss(line);
        Data_Point item;//stores the columns in the row
        std::string tmp;
        int i = 0; //keeps track of the column index
        double x {};
        double y {};

        while(getline(ss, tmp, '\t')) {
            if(i == 4 ){
                x = stod(tmp);
                //std::cout << x << std::endl;
                x_limit(x);
            }
            else if(i == 5 ){
                y = stod(tmp);
                //std::cout << y << std::endl;
                y_limit(y);
            }
            i++;
        }

        item.set_coord(x,y);
        items.push_back(item);
    }
    return items;
}



//void grap_limit_x(int i)

//VECTWODUB read_tsv_2v(char* fname) {
//    std::ifstream ifs(fname);
//    VECTWODUB items; //Stores the x and y coordinate of row in the tsv
//    
//    if (ifs.fail()) { //incase stream fails
//        VECTWODUB err(1,std::vector<double> (1,-1));
//        std::cerr << "error" << std::endl;
//        return err;
//    }
//    std::string line;
//    while (getline(ifs, line)) { //as long as there is input from line
//        std::stringstream ss(line);
//        std::vector<double> item;//stores the columns in the row
//        std::string tmp;
//        int i = 0;
//        while(getline(ss, tmp, '\t')) {
//            if(i == 4 || i == 5){
//                item.push_back(stod(tmp));
//            }
//            i++;
//        }
//        items.push_back(item);
//    }
//    return items;
//}

//void print_v2d(VECTWODUB items){
//    REP(i,items.size()) {
//        REP(j, items[i].size())
//            std::cout << "[" << i << "][" << j <<"]: " << std::setprecision(16) << items[i][j] << std::endl;
//    }
//}



#endif /* read_tsv_h */
