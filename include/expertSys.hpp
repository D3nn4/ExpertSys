#include <string>
#include <vector>
#include "lexer.hpp"

class ExpertSys
{
public:
    ExpertSys(std::string const & file_name);

private:
    Lexer _lexer;
};
