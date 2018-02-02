#include <iostream>
#include "../include/rules.hpp"



std::vector<Fact> const * Rule::getConditions()
{
    return &_conditions;
}

std::vector<Fact> const * Rule::getResults()
{
    return &_results;
}

void Rule::addConditions(std::vector<Fact> const & facts)
{
    _conditions = facts;
}

void Rule::addResults(std::vector<Fact> const & facts)
{
    _results = facts;
}

Fact::Status Rule::checkAnd (Fact currFact,std::map<char, Fact::Status> const & facts)
{
    if (currFact._type == Fact::Type::AND) {
        return facts.find(currFact._data)->second;
    }
    else if (currFact._type == Fact::Type::ANDNOT) {
        if(facts.find(currFact._data)->second == Fact::Status::FALSE) {
            return Fact::Status::TRUE;
        }
        else {
            return Fact::Status::FALSE;
        }
    }
    std::cout << "Error in checkAnd" << std::endl;
    return Fact::Status::FALSE;
}

Fact::Status Rule::checkOr (std::vector<Fact> stack, std::map<char, Fact::Status> const & facts)
{
    Fact currFact;
    while (!stack.empty()) {
        currFact = stack.back();
        stack.pop_back();
        if(currFact._type == Fact::Type::OR
           && (facts.find(currFact._data)->second == Fact::Status::TRUE)){
            return Fact::Status::TRUE;
        }
        else if(currFact._type == Fact::Type::ORNOT
           && (facts.find(currFact._data)->second == Fact::Status::FALSE)){
            return Fact::Status::TRUE;
        }
    }
    return Fact::Status::FALSE;
}

Fact::Status Rule::checkXor(std::vector<Fact> stack, std::map<char, Fact::Status> const & facts)
{
    int trueFact = 0;
    Fact currFact;
    while (!stack.empty()
           && trueFact <= 1) {
        currFact = stack.back();
        stack.pop_back();
        if (currFact._type == Fact::Type::XOR
           && (facts.find(currFact._data)->second == Fact::Status::TRUE)){
            trueFact++;
        }
        else if (currFact._type == Fact::Type::XORNOT
                 && (facts.find(currFact._data)->second == Fact::Status::FALSE)) {
            trueFact++;
        }
    }
    if (trueFact == 1){
        return Fact::Status::TRUE;
    }
    return Fact::Status::FALSE;
}

Fact::Status Rule::checkConditions (std::map<char, Fact::Status> const & facts)
{
    std::vector<Fact> stackCond = _conditions;
    Fact::Status ruleStatus = Fact::Status::TRUE;

    while (!stackCond.empty()
           && ruleStatus == Fact::Status::TRUE) {

        Fact currFact = stackCond.back();
        stackCond.pop_back();
        if (currFact._type == Fact::Type::AND
            || currFact._type == Fact::Type::ANDNOT) {
            ruleStatus = checkAnd(currFact, facts);
        }
        else if (currFact._type == Fact::Type::OR
                 || currFact._type == Fact::Type::ORNOT) {
            std::vector<Fact> stack;
            stack.push_back(currFact);
            currFact = stackCond.back();
            stackCond.pop_back();
            while(!stackCond.empty()
                  && (currFact._type == Fact::Type::OR
                      || currFact._type == Fact::Type::ORNOT)){
                stack.push_back(currFact);
                currFact = stackCond.back();
                stackCond.pop_back();
            }
            ruleStatus = checkOr(stack, facts);
        }
        else if (currFact._type == Fact::Type::XOR
                 || currFact._type == Fact::Type::XORNOT) {
            std::vector<Fact> stack;
            stack.push_back(currFact);
            currFact = stackCond.back();
            stackCond.pop_back();
            while(!stackCond.empty()
                  && (currFact._type == Fact::Type::XOR
                      || currFact._type == Fact::Type::XORNOT)){
                stack.push_back(currFact);
                currFact = stackCond.back();
                stackCond.pop_back();
            }
            ruleStatus = checkXor(stack, facts);
        }
        else {
            std::cout << "Error : unknown rule" << std::endl;
        }
    }
    return ruleStatus;
}

void Rule::applyRule (std::map<char, Fact::Status>& facts)
{

    if (checkConditions(facts) != Fact::Status::TRUE) {
        return;
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
            || currFact._type == Fact::Type::ORNOT
            || currFact._type == Fact::Type::XORNOT
            || currFact._type == Fact::Type::XOR) {
            if(facts[currFact._data] != Fact::Status::TRUE){
                facts[currFact._data] = Fact::Status::UNDETERMINED;
            }
        }
    }
    _isApplied = true;
}
