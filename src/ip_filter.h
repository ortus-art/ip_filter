#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <array>

#include "parse_exception.h"

namespace ip_filter {

using namespace std;

// Representation of IPv4 address octet
using ip_octets = array<uint8_t,4>;
using split_result = tuple<string, string>;
using octets_vector = vector<ip_octets>;

std::ostream& operator<<(std::ostream &stream, ip_filter::ip_octets& octets);

split_result split_line(string line, char delimiter = '\t') noexcept;

ip_octets parse_ip(string value);

octets_vector parse(istream &stream, ostream &log);

void parse_and_print(istream &ins, ostream& outs, ostream &log);


} // namespace ip_filter


