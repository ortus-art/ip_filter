#pragma once

#include <stdexcept>
#include <string>
namespace ip_filter {
class parser_error : public std::logic_error
{
public:
    explicit parser_error(const std::string & arg) : std::logic_error(arg)   { }
};
}
