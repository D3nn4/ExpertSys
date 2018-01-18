#include <string>
#include <vector>

class Lexer
{
public:
    Lexer (std::string const & file_name);
    std::vector<std::string> getRules();
    std::vector<char>        getFacts();
    std::vector<char>        getQueries();

private:

    std::string deleteComments (std::string line);
    void        addFacts (std::string const & line);
    void        addQueries (std::string const & line);

    std::string const &      _file_name;
    std::vector<std::string> _rules;
    std::vector<char>        _facts;
    std::vector<char>        _queries;
};
