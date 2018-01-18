#include <string>
#include <vector>

class Lexer
{
public:
    Lexer (std::string const & file_name);

private:

    std::string _deleteComments (std::string line);
    // std::string _addFacts (std::string line);
    // std::string _addQueries (std::string line);
    // std::string _addRule (std::string line);

    std::string const & _file_name;
    std::vector<std::string> _rules;
    std::vector<char> _facts;
    std::vector<char> _queries;
};
