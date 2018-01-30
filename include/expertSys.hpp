#include <string>
#include <vector>
#include <map>
#include "lexer.hpp"

class ExpertSys
{
public:

    ExpertSys(const std::string& file_name);

    void              applyQueries();

private:
    
    void              applyRules();

    std::map<char, bool> _factsStatus;
    Lexer             _lexer;
    std::vector<Rule> _rules;
    std::vector<char> _facts;
    std::vector<char> _queries;
};
