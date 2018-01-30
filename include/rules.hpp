#include <vector>
#include <map>
#include "node.hpp"

class Rule
{
public :

    bool applyRule (std::map<char, bool>& facts);
    std::vector<Fact>* getConditions();
    std::vector<Fact>* getResults();
    bool              _isApplied = false;

private :

    std::vector<Fact> _conditions;
    std::vector<Fact> _results;


};
