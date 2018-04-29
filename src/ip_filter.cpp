#include "ip_filter.h"

#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>


namespace ip_filter {

std::ostream& operator<<(std::ostream &stream, ip_filter::ip_octets & octets)
{
    stream << static_cast<unsigned>(octets[0])
            << "." << static_cast<unsigned>(octets[1])
            << "." << static_cast<unsigned>(octets[2])
            << "." << static_cast<unsigned>(octets[3])
            << std::endl;
    return stream;
}


split_result split_line(string line, char delimiter) {
  auto pos = line.find_first_of(delimiter);
  auto result = line.substr(0, pos);
  if(string::npos != pos)
  {
      pos++; //Include delimeter;
      line = line.substr(pos);
  }
  else
      line.clear();


  boost::trim(result);
  return std::make_tuple(result, line);
  //return result;
}

ip_octets parse_ip(string value)
{
    std::string oct;
    ip_octets octets = {};
    ip_octets::size_type i = 0;
    std::tie(oct, value) = split_line(value, '.');
    try {
        while (i < 4 && !oct.empty()) {
           octets[i++] = boost::numeric_cast<uint8_t>(boost::lexical_cast<short>(oct));
           std::tie(oct, value) = split_line(value, '.');
        }
    } catch (boost::bad_lexical_cast) {
        throw parser_error("Cannot parse to int");
    } catch (boost::bad_numeric_cast) {
           throw parser_error("Octet out of range");
    }

    if(!value.empty() || !oct.empty() || 4 != i)
        throw parser_error("Failed to parse IP address");
    return octets;
}

octets_vector parse(istream &stream, ostream &log) {
  octets_vector result;
  
  for (std::string value; std::getline(stream, value);) {
    // First extract IP address from string
    std::tie(value, std::ignore) = split_line(value);
    try {
        result.push_back(parse_ip(value));
    } catch (parser_error &e) {
        log << "Error parsing line: " << value << ":" << e.what() << std::endl ;
    }

    
   
  }
  return result;
}

void parse_and_print(istream &ins, ostream& outs, ostream &log)
{
    auto vec = ip_filter::parse(ins, log);
    std::sort(vec.begin(), vec.end(), std::greater<ip_filter::ip_octets>());
    auto end = std::unique(vec.begin(), vec.end());
    vec.erase(end, vec.end());
    for(auto & value: vec)
        outs << value;


}

} // namespace ip_filter
