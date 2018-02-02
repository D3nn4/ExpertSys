#include <vector>
#include <map>
#include "fact.hpp"

class Rule
{
public :

    void                      applyRule (std::map<char, Fact::Status>& facts);
    std::vector<Fact> const * getConditions();
    std::vector<Fact> const * getResults();
    void                      addConditions(std::vector<Fact> const & facts);
    void                      addResults(std::vector<Fact> const & facts);
    bool                      _isApplied = false;

private :

    Fact::Status      checkConditions (std::map<char, Fact::Status>const & facts);
    Fact::Status      checkAnd (Fact currFact, std::map<char, Fact::Status>const & facts);
    Fact::Status      checkOr (std::vector<Fact> stack, std::map<char, Fact::Status>const & facts);
    Fact::Status      checkXor (std::vector<Fact> stack, std::map<char, Fact::Status>const & facts);
    std::vector<Fact> _conditions;
    std::vector<Fact> _results;


};
