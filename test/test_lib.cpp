#include <QtTest/QtTest>

#include "lexicon.h"
#include "qamus.h"

class Test: public QObject
{
        Q_OBJECT
    public Q_SLOTS:
        void init();


    private slots:
        void qamusLoadFile_data();
        void qamusLoadFile();
};

void Test::init()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
}


void Test::qamusLoadFile_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<bool>("load");
    QTest::addColumn<int>("col");
    QTest::addColumn<int>("row");

    QTest::newRow("non-existant dictionary") << "null.qlx"  << false << 0 << 0;
    QTest::newRow("empty dictionary")        << "empty.qlx" << true  << 0 << 0;
    QTest::newRow("small dictionary")        << "small.qlx" << true  << 1 << 1;
    QTest::newRow("large dictionary")        << "large.qlx" << true  << 5 << 10448;
}

void Test::qamusLoadFile()
{
    QFETCH(QString, filename);
    QFETCH(bool, load);
    QFETCH(int, col);
    QFETCH(int, row);

    Qamus qamus;
    QCOMPARE(qamus.loadLexicon(QString("data/") + filename), load);
    QCOMPARE(qamus.columnCount(), col);
    QCOMPARE(qamus.rowCount(), row);
}

QTEST_MAIN(Test)
#include "test_lib.moc"
