#include <iostream>
#include <fstream>
#include "../include/lexer.hpp"
Lexer::Lexer (std::string const & file_name)
    :_file_name (file_name)
{
    std::string line;
    std::ifstream myfile (file_name, std::ifstream::in);
    if (myfile.is_open())
        {
            while (std::getline (myfile,line)) {
                line = _deleteComments(line);
                if(!line.empty()) {
                    std::cout << line << std::endl;
                }
                if (line[0] == '=') { // get facts
                    // LATER: check validity
                    for (char& elem: line) {
                        if(elem != '=') {
                            _facts.push_back(elem);
                        }
                    }
                }
                else if (line[0] == '?') { // get queries
                    // LATER: check validity
                    for (char& elem: line) {
                        if(elem != '=') {
                            _queries.push_back(elem);
                        }
                    }
                }
            }
            myfile.close();
        }
    else {
        std::cout << "Unable to open file" << std::endl; 
    }
}

std::string Lexer::_deleteComments (std::string line)
{
    size_t pos = line.find_first_of ("#");
    if (pos != std::string::npos) {
        line.erase(pos);
    }
    return line;
}
