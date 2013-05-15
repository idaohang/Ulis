#ifndef SIMPLEGPXREADER_H
#define SIMPLEGPXREADER_H

#include <QIODevice>

#include "SimpleGPXReader_global.h"

#include "TraceData.h"

class SIMPLEGPXREADERSHARED_EXPORT SimpleGPXReader
{
public:
    static  Trace* parseData(QIODevice * data);
private:
    SimpleGPXReader();
};

#endif // SIMPLEGPXREADER_H
