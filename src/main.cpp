#include <iostream>

#include "ip_filter.h"

using namespace std;

int main()
{
    try {

        auto vec = ip_filter::parse(std::cin, std::cerr);
        std::sort(vec.begin(), vec.end(), std::greater<ip_filter::ip_octets>());
        ip_filter::print_octets(vec, std::cout);
        ip_filter::filter_and_print(vec, std::cout, 1);
        ip_filter::filter_and_print(vec, std::cout, 46, 70);
        ip_filter::filter_any_and_print(vec, std::cout, 46);

    } catch (std::exception &e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}
