#ifndef QREADGPX_H
#define QREADGPX_H

#include <QXmlSimpleReader>

class QReadGPX : public TraceReaderInterface
{
public:
    TraceData parseData(QIODevice data);

private:
    QReadGPX();
    QReadGPX(&QReadGPX);

};

#endif // QREADGPX_H
