//
//  read_tsv.h
//  unary_encodingV2
//
//  Created by MJ Asuncion on 11/19/22.
//

#ifndef read_tsv_h
#define read_tsv_h
void read_tsv(char* fname) {
    std::ifstream ifs(fname);
    
    if (ifs.fail()) { //incase stream fails
        std::cerr << "error" << std::endl;
        return;
    }
    std::string line;
    while (getline(ifs, line)) { //as long as there is input from line
        std::stringstream ss(line);
        std::vector<std::string> item;//stores the columns in the row
        std::string tmp;
        while(getline(ss, tmp, '\t')) {
            item.push_back(tmp);
        }
        items.push_back(item);
    }
    REP(i,items.size()) {
        REP(j, items[i].size())
            std::cout << "[" << i << "][" << j <<"]: " << items[i][j] << std::endl;
    }
    return;
}

//void extract_location(


#endif /* read_tsv_h */
