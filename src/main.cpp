#include <iostream>

#include "common.h"
#include "ip_filter.h"

using namespace std;

int main()
{
   ip_filter::parse_and_print(std::cin, std::cout, std::cerr);
    return 0;
}
