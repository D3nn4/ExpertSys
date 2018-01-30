#include <string>
#include <vector>
#include "lexer.hpp"

class ExpertSys
{
public:
    ExpertSys(const std::string& file_name);
    void applyQueries();
private:
    Lexer _lexer;
    std::vector<Rule> _rules;
    std::vector<char>        _facts;
    std::vector<char>        _queries;
};
