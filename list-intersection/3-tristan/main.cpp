#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>

int main(int argc, char **argv)
{
    std::unordered_set<std::string> words;
    std::vector<std::string> dupes;

    if (argc != 3) {
        return -1;
    }

    std::fstream words1(argv[1]);
    if (!words1.is_open()) {
        return -1;
    }

    std::fstream words2(argv[2]);
    if (!words2.is_open()) {
        return -1;
    }

    std::string word;

    while (words1) {
        std::getline(words1, word);
        words.insert(word);
    }

    while (words2) {
        std::getline(words2, word);
        auto result = words.insert(word);
        if (!result.second) {
            dupes.push_back(word);
        }
    }

    std::sort(dupes.begin(), dupes.end());

    std::stringstream out;
    for (auto dupe : dupes) {
        out << dupe << std::endl;
    }

    std::cout << out.str();

    return 0;
}
