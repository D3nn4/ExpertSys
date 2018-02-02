#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "../include/lexer.hpp"

bool Lexer::isValidFactOrQuery(std::string const & line)
{
    for (size_t i = 1; i < line.size(); i++) {
        if(line[i] != ' '){
            if (line[i] < 'A' || 'Z' < line[i]) {
                if(line[0] == '=')
                    std::cout << "Error : invalid facts.\n";
                else
                    std::cout << "Error : invalid queries.\n";
                return false;
            }
        }
    }
    return true;
}

bool Lexer::isValidRules(std::string const & line)
{
    bool isFact = true;
    std::vector<std::string> tokens;
    boost::split(tokens, line, [](char c){return c == ' ';});
    for (std::string& elem : tokens) {
        if (isFact) {
            if ((elem.size() > 2)
                ||((elem.size() == 2) && (elem[0] != '!' || (elem[1] < 'A' || 'Z' < elem[1])))
                ||((elem.size() == 1) && (elem[0] < 'A' || 'Z' < elem[0]))){
                std::cout << "Error : invalid rules.\n";
                return false;
            }
        }
        else {
            if(elem.size() > 2
               || (elem.size() == 2 && elem.compare("=>") != 0)
               || (elem.size() == 1 && (elem.find_first_not_of("+|^") != std::string::npos))){
                std::cout << "Error : invalid rules.\n";
                return false;
            }
        }
        isFact = !isFact;
    }
    return true;
}

Lexer::Lexer (std::string const & file_name)
    :_file_name (file_name)
{
    std::string line;
    std::ifstream myfile (file_name, std::ifstream::in);
    if (myfile.is_open())
        {
            while (std::getline (myfile,line)) {
                line = deleteComments(line);
                if(!line.empty()) {
                    if (line[0] == '=') {
                        if(isValidFactOrQuery(line)){
                            addFacts(line);
                        }
                        else {
                            return;
                        }
                    }
                    else if (line[0] == '?') {
                        if(isValidFactOrQuery(line)){
                            addQueries(line);
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        if(isValidRules(line)){
                            addRules(line);
                        }
                        else {
                            return;
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

std::vector<Rule> Lexer::getRules()
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
    for (char const & elem: line) {
        if(elem != '=' && elem != ' ') {
            _facts.push_back(elem);
        }
    }
}

void Lexer::addQueries (std::string const & line)
{
    for (char const & elem: line) {
        if(elem != '?' && elem != ' ') {
            _queries.push_back(elem);
        }
    }
}

void Lexer::addRules (std::string const & line)
{
    std::vector<std::string> tokens;
    boost::split(tokens, line, [](char c){return c == ' ';});

    Rule newRule;
    Fact::Type currentType = Fact::Type::AND;
    std::vector<Fact> currentVector;
    for (std::string& elem : tokens) {
        Fact newFact;
        newFact._type = currentType;
        currentType = Fact::Type::AND;
        if ('A' <= elem[0] && elem[0] <= 'Z') {
            newFact._data = elem[0];
            currentVector.push_back(newFact);
        }
        else if (elem[0] == '!') {
            newFact._data = elem[1];
            if(newFact._type == Fact::Type::AND){
                newFact._type = Fact::Type::ANDNOT;
            }
            else if(newFact._type == Fact::Type::XOR){
                newFact._type = Fact::Type::XORNOT;
            }
            else if(newFact._type == Fact::Type::OR){
                newFact._type = Fact::Type::ORNOT;
            }
            else {
                std::cout << "Error : Type not known" << std::endl;
            }
            currentVector.push_back(newFact);
        }
        else if (elem[0] == '|') {
            currentType = Fact::Type::OR;
            currentVector.back()._type = currentType;
        }
        else if (elem[0] == '^') {
            currentType = Fact::Type::XOR;
            currentVector.back()._type = currentType;
        }
        else if (elem[0] == '=') {
            newRule.addConditions(currentVector);
            currentVector.clear();
        }
    }
    newRule.addResults(currentVector);
    _rules.push_back(newRule);
}
