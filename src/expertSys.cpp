#include <iostream>
#include <fstream>
#include "../include/expertSys.hpp"

ExpertSys::ExpertSys(std::string const & file_name)
    :_lexer(file_name)
{
    _rules = _lexer.getRules();
    _facts = _lexer.getFacts();
    _queries = _lexer.getQueries();
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
        bool ruleApplied = false;
        if (!_rules[i]._isApplied) {
            _rules[i].applyRule(_factsStatus);
            ruleApplied = _rules[i]._isApplied;
        }
        if(!ruleApplied) {
            i++;
        }
        else {
            i = 0;
        }
    }
}

static void printStatus(Fact::Status status)
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

void ExpertSys::applyQueries()
{
    for (auto& query : _queries) {
        // for (auto& query : _factsStatus) {
        std::cout << query << " is ";
        printStatus(_factsStatus[query]);
        std::cout << std::endl;
    }
}
