#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <iostream>
#include <algorithm>

int main ()
{
    std::ifstream a_src ("words.1"), b_src ("words.2");
    std::set<std::string> a_values, b_values;

    for (std::string line; std::getline (a_src, line);)
        a_values.insert (line);
    for (std::string line; std::getline (b_src, line);)
        b_values.insert (line);

    std::set_intersection (
        std::begin (a_values), std::end (a_values),
        std::begin (b_values), std::end (b_values),
        std::ostream_iterator<std::string> (std::cout, "\n")
    );
}
