#ifndef TRACEREADERINTERFACE_H
#define TRACEREADERINTERFACE_H

#include "tracedata.h"

class TraceReaderInterface
{
public:
    virtual static TraceData parseData(QIODevice data) = NULL;
};

#endif // TRACEREADERINTERFACE_H
