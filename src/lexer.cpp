#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "../include/lexer.hpp"

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
                    // std::cout << line << std::endl;
                    if (line[0] == '=') {
                        addFacts(line);
                    }
                    else if (line[0] == '?') {
                        addQueries(line);
                    }
                    else {
                        addRules(line);
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

void Lexer::addRules (std::string const & line)
{
    std::vector<std::string> tokens;
    boost::split(tokens, line, [](char c){return c == ' ';});

    Rule newRule;
    Fact::Type currentType = Fact::Type::AND;
    std::vector<Fact>* currentVector = newRule.getConditions();
    for (std::string& elem : tokens) {
        Fact newFact;
        newFact._type = currentType;
        currentType = Fact::Type::AND;
        if ('A' <= elem[0] && elem[0] <= 'Z') {
            newFact._data = elem[0];
            currentVector->push_back(newFact);
        }
        else if (elem[0] == '!') {
            newFact._data = elem[1];
            newFact._type = Fact::Type::ANDNOT;
            currentVector->push_back(newFact);
        }
        else if (elem[0] == '|') {
            currentType = Fact::Type::OR;
            currentVector->back()._type = currentType;
        }
        else if (elem[0] == '^') {
            currentType = Fact::Type::XOR;
            currentVector->back()._type = currentType;
        }
        else if (elem[0] == '=') {
            currentVector = newRule.getResults();
        }
        //TODO XORNOT ORNOT IFANDONLYIF

    }
    // std::cout << newRule._conditions.size() << std::endl;
    // std::cout << newRule._result.size() << std::endl;
    // std::cout << std::endl;
    _rules.push_back(newRule);
}
