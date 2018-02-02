#include <string>
#include <vector>
#include "rules.hpp"

class Lexer
{
public:
    Lexer (std::string const & file_name);
    std::vector<Rule> getRules();
    std::vector<char> getFacts();
    std::vector<char> getQueries();

private:

    std::string deleteComments (std::string line);
    void        addFacts (std::string const & line);
    void        addQueries (std::string const & line);
    void        addRules (std::string const & line);
    bool        isValidFactOrQuery(std::string const & line);
    bool        isValidRules(std::string const & line);

    std::string const & _file_name;
    std::vector<Rule>   _rules;
    std::vector<char>   _facts;
    std::vector<char>   _queries;
};
