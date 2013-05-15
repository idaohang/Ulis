#include <QString>
#include <QtTest>

#include "simplegpxreader.h"
#include <QDir>
#include <memory>
#include <QDebug>

class SimpleGPXReader_Test : public QObject
{
    Q_OBJECT
    
public:
    SimpleGPXReader_Test();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void parseDataTst();
    void TracePoint_OperatorEqual_Tst();
    void parseDataTst_data();
};

SimpleGPXReader_Test::SimpleGPXReader_Test()
{
}

void SimpleGPXReader_Test::initTestCase()
{
}

void SimpleGPXReader_Test::cleanupTestCase()
{
}

/**
 * @brief SimpleGPXReader_Test::parseDataTst
 * Test de la fonction de SimpleGPXReader:
 * TracePoint * SimpleGPXReader::parseData(QIODevice * data)
 */
void SimpleGPXReader_Test::parseDataTst()
{
    QFETCH(QString, filename);
    QFETCH(Trace*, result);

    QIODevice* dev = new QFile(filename);
    Trace * resLib = SimpleGPXReader::parseData(dev);

    QCOMPARE(*result, *resLib);


    delete dev;
    delete resLib;
}

void SimpleGPXReader_Test::TracePoint_OperatorEqual_Tst() {
    TracePoint tr_null;
    TracePoint ramp(1.0d, 2.0d, QDateTime::fromString("2013-11-20", "yyyy-MM-dd"), 3.0d);
    TracePoint ramp2(1.1d, 2.0d, QDateTime::fromString("2013-11-20", "yyyy-MM-dd"), 3.0d);
    TracePoint ramp3(1.1d, 2.0d, QDateTime::fromString("2014-11-20", "yyyy-MM-dd"), 3.0d);
    TracePoint ramp_copy = ramp;

    QVERIFY(tr_null == tr_null);
    QVERIFY(tr_null != ramp);
    QVERIFY(ramp == ramp_copy);
    QVERIFY(ramp3 != ramp2);
    QVERIFY(ramp3 != ramp);
    QVERIFY(tr_null.alt == 0);
    QVERIFY(ramp2.alt == 3.0d);
    QVERIFY(ramp2.lon == 1.1d);
    QVERIFY(ramp3.lat == 2.0d);

}

void SimpleGPXReader_Test::parseDataTst_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<Trace*>("result");

    Trace* noTc = new Trace();
    Track* noTr = new Track();
    noTr->setName(QString("Example GPX Document"));
    noTc->add(noTr);
    QTest::newRow("No track") << QString("txt_GPX_NoTrack.gpx") << noTc;

    Trace* TcOneWpt = new Trace();
    Track* oneWpt = new Track();
    oneWpt->setName(QString("Example GPX Document"));

    Segment* s = new Segment();
    s->add(
        TracePoint(
           QString("-122.326897").toDouble(),
           QString("47.644548").toDouble(),
           QDateTime::fromString("2009-10-17T18:37:26Z", Qt::ISODate),
           QString("4.46").toDouble())
    );


    oneWpt->add(s);
    TcOneWpt->add(oneWpt);
    QTest::newRow("One Wpt") << QString("txt_GPX_OneTrk.gpx") << TcOneWpt;
}

QTEST_APPLESS_MAIN(SimpleGPXReader_Test)

#include "simplegpxreader_test.moc"
