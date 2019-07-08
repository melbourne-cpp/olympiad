#include <list>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
list<string> readFile(string);
void writeFile(list<string>, string);
int main()
{
    list<string> listA = readFile("words.1");
    list<string> listB = readFile("words.2");
    list<string> matches;
    listA.sort();
    listB.sort();
    list<string>::const_iterator itA = listA.begin();
    list<string>::const_iterator itB = listB.begin();
    while (itA != listA.end() && itB != listB.end())
    {
        int equal = (*itA).compare(*itB);
        if (equal == 0)
        {
            matches.push_back(*itA);
            itA++;
            itB++;
        }
        else if (equal > 0) // Char in A is less then char in B
        {
            itB++;
        }
        else
        {
            itA++;
        }
    }
    writeFile(matches, "output");
    return 0;
}
list<string> readFile(string path)
{
    list<string> words;
    ifstream file(path);
    string line;
    while (getline(file, line))
    {
        words.push_back(line);
    }
    return words;
}
void writeFile(list<string> data, string path)
{
    ofstream outFile(path);
    list<string>::iterator it;
    for (it = data.begin(); it != data.end(); it++)
    {
        outFile << *it << "\n";
    }
}
