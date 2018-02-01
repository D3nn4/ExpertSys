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
void printType(Fact::Type type);//////////////////////
Fact::Status Rule::checkConditions (std::map<char, Fact::Status> const & facts)
{
    std::vector<Fact> stackCond = _conditions;
    Fact::Status statusRule = Fact::Status::TRUE;
    // std::cout << "There is " << stackCond.size() << " conditions" << std::endl;
    while (!stackCond.empty()
           && statusRule == Fact::Status::TRUE) {
        Fact currFact = stackCond.back();
        stackCond.pop_back();
        // std::cout << currFact._data;
        // printType(currFact._type);
        // std::cout << std::endl;
        if (currFact._type == Fact::Type::AND) {
            statusRule = facts.find(currFact._data)->second;
        }
        else if (currFact._type == Fact::Type::ANDNOT) {
            if(facts.find(currFact._data)->second == Fact::Status::FALSE) {
                statusRule = Fact::Status::TRUE;
            }
            else {
                statusRule = Fact::Status::FALSE;
            }
        }
        // else if (currFact._type == Fact::Type::OR) {
        //     //TODO ORNOT
        //     statusRule = Fact::Status::FALSE;
        //     while (currFact._type == Fact::Type::OR) {
        //         if(facts.find(currFact._data)->second == Fact::Status::TRUE) {
        //             statusRule = Fact::Status::TRUE;
        //         }
        //         currFact = stackCond.back();
        //         stackCond.pop_back();
        //     }
        // }
        // else if (currFact._type == Fact::Type::XOR) {
        //     // statusRule = checkXOR();
        //     //TODO XORNOT
        // }
        else {
            std::cout << "Error : unknown rule" << std::endl;
        }
    }
    return statusRule;
}

bool Rule::applyRule (std::map<char, Fact::Status>& facts)
{

    if (checkConditions(facts) != Fact::Status::TRUE) {
        // std::cout << "do not apply rule" << std::endl;
        return false;
    }
    std::vector<Fact> stackResult = _results;
    while(!stackResult.empty()) {
        Fact currFact = stackResult.back();
        stackResult.pop_back();
        if (currFact._type == Fact::Type::AND) {
            facts[currFact._data] = Fact::Status::TRUE;
        }
        else if (currFact._type == Fact::Type::ANDNOT) {
            facts[currFact._data] = Fact::Status::FALSE;
        }
        if (currFact._type == Fact::Type::OR
            || currFact._type == Fact::Type::XOR) {
            facts[currFact._data] = Fact::Status::UNDETERMINED;
        }
    }
    _isApplied = true;
    std::cout << "apply rule" << std::endl;
    return true;
}
