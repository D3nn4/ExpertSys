#include <vector>
#include <map>
#include "fact.hpp"

class Rule
{
public :

    bool applyRule (std::map<char, Fact::Status>& facts);
    std::vector<Fact>* getConditions();
    std::vector<Fact>* getResults();
    bool              _isApplied = false;

private :

    Fact::Status checkConditions (std::map<char, Fact::Status>const & facts);
    std::vector<Fact> _conditions;
    std::vector<Fact> _results;


};
