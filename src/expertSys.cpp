#include <iostream>
#include <fstream>
#include "../include/expertSys.hpp"

ExpertSys::ExpertSys(std::string const & file_name)
    :_lexer(file_name)
{
    _rules = _lexer.getRules();
    _facts = _lexer.getFacts();
    _queries = _lexer.getQueries();
    std::cout << _rules.size() << std::endl;
    char fact = 'A';
    for (; fact <= 'Z'; fact++) {
        _factsStatus.insert(std::pair<char,Fact::Status>(fact, Fact::Status::FALSE));
    }
    for (char& trueFact : _facts) {
        _factsStatus[trueFact] = Fact::Status::TRUE;
    }
    applyRules();
}

void ExpertSys::applyRules()
{
    size_t i = 0;
    while (i < _rules.size()) {
        // std::cout << "rule nb " << i << std::endl;
        bool ruleApplied = false;
        if (!_rules[i]._isApplied) {
            // std::cout << "try to apply rule" << std::endl;
            ruleApplied = _rules[i].applyRule(_factsStatus);
        }
        if(!ruleApplied) {
            i++;
        }
        else {
            i = 0;
        }
    }
    // std::cout << "end of apply rule" << std::endl;

}

void printStatus(Fact::Status status)
{
    
    if(status == Fact::Status::TRUE) {
        std::cout << " true ";
    }
    else if(status == Fact::Status::FALSE) {
        std::cout << " false ";
    }
    else {
        std::cout << " undetermined ";
    }
}
void printType(Fact::Type type)
{
    
    if(type == Fact::Type::AND) {
        std::cout << " AND ";
    }
    else if(type == Fact::Type::OR) {
        std::cout << " OR ";
    }
    else if(type == Fact::Type::XOR) {
        std::cout << " XOR ";
    }
    else if(type == Fact::Type::ANDNOT) {
        std::cout << " ANDNOT ";
    }
    else {
        std::cout << " UNKNOWN TYPE ";
    }
}


void ExpertSys::applyQueries()
{
    for (auto& query : _queries) {
        std::cout << query << " is ";
        printStatus(_factsStatus[query]);
        std::cout << std::endl;
    }
}
