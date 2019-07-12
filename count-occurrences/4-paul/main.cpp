#include <QFile>
#include <QTextStream>
#include <iostream>

int main()
{
    // Open the numbers file for reading.
    QFile file("numbers");
    file.open(QFile::ReadOnly);

    // Count the frequency of each number.
    QHash<int, int> counts;
    QTextStream stream(&file);
    stream.setIntegerBase(10); // Not necessary, just disables auto-detection (so slightly faster).
    for (int number; (stream >> number).status() == QTextStream::Ok;) {
        ++counts[number];
    }

    // Generate a list of <count,number> pairs.
    QList<QPair<int,int>> pairs;
    pairs.reserve(counts.size());
    for (auto iter = counts.constBegin(); iter != counts.constEnd(); ++iter) {
        pairs.append({iter.value(), iter.key()});
    }

    // Sort, and output the list of numbers with counts.
    std::sort(pairs.begin(), pairs.end(), std::less<>());
    for (const auto &pair: pairs) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
    return EXIT_SUCCESS;
}
