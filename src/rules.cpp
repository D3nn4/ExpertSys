#include <iostream>
#include "../include/rules.hpp"


std::vector<Fact>* Rule::getConditions()
{
    return &_conditions;
}

std::vector<Fact>* Rule::getResults()
{
    return &_results;
}

bool Rule::applyRule (std::map<char, bool>& facts)
{
    std::vector<Fact> stackCond = _conditions;
    bool statusRule = true;

    while (!stackCond.empty()
           && statusRule == true) {
        Fact currFact = stackCond.back();
        stackCond.pop_back();
        if (currFact._type == Fact::Type::AND) {
            statusRule = facts[currFact._data];
        }
        else if (currFact._type == Fact::Type::ANDNOT) {
            statusRule = !facts[currFact._data];
        }
        else if (currFact._type == Fact::Type::OR) {
            // statusRule = checkOR();
        }
        else if (currFact._type == Fact::Type::XOR) {
            // statusRule = checkXOR();
        }
    }

    if (statusRule) {
        _isApplied = true;
        std::cout << "apply rule" << std::endl;
    }
    else {
        
        std::cout << "do not apply rule" << std::endl;
    }

    return statusRule;
}
