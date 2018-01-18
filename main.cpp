#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "include/expertSys.hpp"

int main (int argc, char** argv)
{
    if (argc == 1) {
        std::cout << "No file to read" << std::endl;
    }
    else if (argc > 2) {
        std::cout << "Too many arguments" << std::endl;
    }
    else {
        std::string const file_name = argv[1];
        ExpertSys expSys(file_name);
    }

    return 0;
}
