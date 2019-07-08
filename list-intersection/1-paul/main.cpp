#include <QDebug>
#include <QFile>

int main(int, const char * [])
{
    QFile words1("words.1");
    words1.open(QFile::ReadOnly);
    const auto list = words1.readAll().split('\n').toSet();

    QFile words2("words.2");
    words2.open(QFile::ReadOnly);
    auto list2 = words2.readAll().split('\n');
    qSort(list2.begin(), list2.end());

    foreach (const QByteArray &word, list2)
    {
        if (list.contains(word)) {
            qInfo().noquote() << word;
        }
    }
    return EXIT_SUCCESS;
}
