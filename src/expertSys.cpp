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
        _factsStatus.insert(std::pair<char,bool>(fact, false));
    }
    for (char& trueFact : _facts) {
        _factsStatus[trueFact] = true;
    }
    applyRules();
}

void ExpertSys::applyRules()
{
    size_t i = 0;
    while (i < _rules.size()) {
        std::cout << "rule nb " << i << std::endl;
        bool ruleApplied = false;
        if (!_rules[i]._isApplied) {
            std::cout << "try to apply rule" << std::endl;
            ruleApplied = _rules[i].applyRule(_factsStatus);
        }
        if(!ruleApplied) {
            i++;
        }
        else {
            i = 0;
        }
    }
    std::cout << "end of apply rule" << std::endl;

}

void ExpertSys::applyQueries()
{
    for (auto& query : _queries) {
        std::cout << query << " is ";
        if(_factsStatus[query] == true) {
            std::cout << " true " << std::endl;
        }
        else {
            std::cout << " false " << std::endl;
        }
    }
}
