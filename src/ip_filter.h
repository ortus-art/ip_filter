#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <array>
#include <type_traits>
#include "parse_exception.h"

#include <boost/range/adaptor/filtered.hpp>

namespace ip_filter {

using namespace std;

using ip_octet = uint8_t;
// Representation of IPv4 address octet
using ip_octets = array<ip_octet,4>;
using split_result = tuple<string, string>;
using octets_vector = vector<ip_octets>;


std::ostream& operator<<(std::ostream &stream, const ip_filter::ip_octets& octets);

split_result split_line(string line, const char delimiter = '\t');

ip_octets parse_ip(string value);

octets_vector parse(istream &stream, ostream &log);

void parse_and_print(istream &ins, ostream& outs, ostream &log);

template<typename Lambda>
inline auto filter_vector(ip_filter::octets_vector& vec, const Lambda & fun)
{
    using namespace boost::adaptors;
    return vec | filtered(fun);
}

template<typename... Octs >
auto filter_predicate(Octs... args)
{
    static_assert (sizeof... (args) < 4, "IP octet vector cannot contain more than 4 elements" );
    return [=](ip_octets & value)
    {
        int filter[sizeof...(args)] = {args...};
        auto i = 0;
        auto result = true;
        for(const auto& val: filter)
        {
            if (!(result = (value[i++] == val)))
                break;
        }
        return result;
    };
}



template<typename... Octs >
auto filter_any_predicate(Octs... args)
{
    static_assert (sizeof... (args) !=0 , "This function requires filtering value" );
    auto params = {args...};
    return [=](ip_octets & value)
    {
        int filter[sizeof...(args)] = {args...};
        auto result = false;
        for(const auto & val: filter)
        {
           for(const auto & inner : value)
               if ((result = (inner == val)))
                break;
        }
        return result;
    };
}


template <typename Data>
void print_octets(const Data& data,  ostream& out)
{
    for(const auto & item: data)
           out << item;
}

template<typename... Octs >
auto filter_by_address_and_print(ip_filter::octets_vector& vec, ostream& out,  Octs... args)
{
    auto predicate = filter_predicate(args...);
    auto view = filter_vector(vec, predicate);
    print_octets(view, out);
}

template<typename... Octs >
auto filter_by_any_part_of_address_and_print(ip_filter::octets_vector& vec, ostream& out,  Octs... args)
{
    auto predicate = filter_any_predicate(args...);
    auto view = filter_vector(vec, predicate);
    print_octets(view, out);
}



} // namespace ip_filter


