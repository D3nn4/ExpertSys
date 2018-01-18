#include <iostream>
#include <fstream>
#include "../include/expertSys.hpp"

ExpertSys::ExpertSys(std::string const & file_name)
    :_lexer(file_name)
{
}
