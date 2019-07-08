#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Take one number from the string 'start' of length 'remain'.
// Returns the value that was parsed.
// Updates the string point and remaining characters in place.
int extract_number (char const *&start, ssize_t &remain)
{
    int res = 0;

    while (remain--) {
        switch (auto const &c = *start++; c) {
            case '0'...'9':
                res *= 10;
                res += c - '0';
                break;

            default:
                return res;
        }
    }

    return res;
}

// The maximum index we will read
static constexpr int ELEMENTS = 50'001;

int main ()
{
    // Open up the data file
    auto const fd = open ("numbers", O_RDONLY);
    auto const size = [&] () {
        struct stat buf;
        fstat (fd, &buf);
        return buf.st_size;
    } ();

    auto *const _data = mmap (nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
    auto *       data = reinterpret_cast<const char*> (_data);

    // Set the number of occurences of each to 0
    std::vector<int> counts (ELEMENTS, 0);

    // Read one number and increment its count
    for (auto remain = size; remain; ) {
        auto const idx = extract_number (data, remain);
        ++counts[idx];
    }

    // Allocate an array that contains each index
    std::vector<int> indices (ELEMENTS);
    std::iota (std::begin (indices), std::end (indices), 0);

    // Sort the indices based on the count seen
    std::sort (
        std::begin (indices),
        std::end   (indices),
        [&counts]  (auto const &a, auto const &b)
    {
        if (counts[a] < counts[b])
            return true;
        if (counts[a] == counts[b])
            return a < b;
        return false;
    });

    // Print the tally
    for (int i = 1; i < indices.size (); ++i) {
        auto const idx = indices[i];
        std::cout << counts[idx] << ' ' << idx << '\n';
    }
}
