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
                    // std::cout << line << std::endl;
                    if (line[0] == '=') {
                        _addFacts(line);
                    }
                    else if (line[0] == '?') {
                        _addQueries(line);
                    }
                    else {
                        //TODO rules
                    }
                }
            }
            myfile.close();
        }
    else {
        std::cout << "Unable to open file" << std::endl; 
    }
}

std::vector<std::string> Lexer::getRules()
{
    return _rules;
}

std::vector<char> Lexer::getFacts()
{
    return _facts;
}

std::vector<char> Lexer::getQueries()
{
    return _queries;
}

std::string Lexer::deleteComments (std::string line)
{
    size_t pos = line.find_first_of ("#");
    if (pos != std::string::npos) {
        line.erase(pos);
    }
    return line;
}
void Lexer::addFacts (std::string const & line)
{
    // LATER: check validity
    for (char const & elem: line) {
        if(elem != '=' && elem != ' ') {
            _facts.push_back(elem);
        }
    }
    // std::cout << "there is " << _facts.size() << " facts." << std::endl;
    // for(auto& elem : _facts) {
    //     std::cout << elem << std::endl;
    // }
}

void Lexer::addQueries (std::string const & line)
{
    // LATER: check validity
    for (char const & elem: line) {
        if(elem != '?' && elem != ' ') {
            _queries.push_back(elem);
        }
    }
    // std::cout << "there is " << _queries.size() << " queries." << std::endl;
    // for(auto& elem : _queries) {
    //     std::cout << elem << std::endl;
    // }
}
