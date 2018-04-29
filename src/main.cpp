#include <iostream>

#include "ip_filter.h"

using namespace std;

int main()
{
    try {
        ip_filter::parse_and_print(std::cin, std::cout, std::cerr);
    } catch (std::exception &e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}
