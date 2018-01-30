#include <vector>
#include "node.hpp"

struct Rule
{
    bool applyRule (std::vector<char>& facts);

    bool              _isApplied = false;
    std::vector<Fact> _conditions;
    std::vector<Fact> _result;


};
