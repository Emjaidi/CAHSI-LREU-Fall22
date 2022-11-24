#include "read_tsv.h"
#include "Data_Point.h"

int main()
{
    std::vector<Data_Point> coordinates = read_tsv((char *)"test.txt");
    REP(i, coordinates.size())
    {
        std::cout << "User: " << i;
        std::cout << " ";
        coordinates.at(i).print_coord();
        
    }
    std::cout << "\nx[min,max] and y[min,max] limits are: [" << min_x << ", "
        << max_x << "][" << min_y << ", " << max_y << "]\n";
    //print_v2d(coordinates);
    //std::cout << 'g';

    return 0;
}