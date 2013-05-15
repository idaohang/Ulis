#ifndef TRACEPOINT_H
#define TRACEPOINT_H

#include <QMetaType>
#include <QDateTime>
#include <QDebug>

#include "Node.h"

#include "SimpleGPXReader_global.h"

struct SIMPLEGPXREADERSHARED_EXPORT TracePoint{

public :
    double lon;
    double lat;
    double alt;
    QDateTime time;

    TracePoint(): lon(0), lat(0), alt(0), time(QDateTime()) { }

    TracePoint(const TracePoint & o): lon(o.lon), lat(o.lat), alt(o.alt), time(o.time) {}

    ~TracePoint() {}

    TracePoint(double _lon, double _lat, QDateTime _time, double _alt = -1 ) : lon(_lon), lat(_lat), alt(_alt), time(_time) {}

    bool operator==(const TracePoint& t) const;
    bool operator!=(const TracePoint& t) const { return ! (*this == t); }
};

QDebug SIMPLEGPXREADERSHARED_EXPORT operator<<(QDebug dbg, const TracePoint& Obj);



class SIMPLEGPXREADERSHARED_EXPORT Segment: public Node_Template<TracePoint>, public Node_QT {
public:
    //void setDescription(QString  desc);
    //QString description();
    //void setName(QString name);
    //QString name();
    void add(TracePoint newElt);
    TracePoint pop(int index);
    void change(int index, TracePoint elt);
    //int length();
    const TracePoint & operator[](int index);
    bool operator==(const Segment &t1) const;
    bool operator!=(const Segment &t1) const { return !(*this == t1); }
};


class SIMPLEGPXREADERSHARED_EXPORT Track: public Node_Template<Segment*>, public Node_QT {
public:
    //void setDescription(QString  desc);
    //QString description();
    //void setName(QString name);
    //QString name();
    void add(Segment* newElt);
    Segment* pop(int index);
    void change(int index, Segment* elt);
    //int length();
    const Segment* & operator[](int index);
    bool operator==(const Track &t1) const;
    bool operator!=(const Track &t1) const { return !(*this == t1); }
    ~Track();
};

class SIMPLEGPXREADERSHARED_EXPORT Trace: public Node_Template<Track*>, public Node_QT {
public:
    //void setDescription(QString  desc);
    //QString description();
    //void setName(QString name);
    //QString name();
    void add(Track* newElt);
    Track* pop(int index);
    void change(int index, Track* elt);
    //int length();
    const Track* & operator[](int index);
    bool operator==(const Trace &t1) const;
    bool operator!=(const Trace &t1) const { return !(*this == t1); }
    ~Trace();
};

Q_DECLARE_METATYPE(Trace*)
Q_DECLARE_METATYPE(Track*)
Q_DECLARE_METATYPE(Segment*)
Q_DECLARE_METATYPE(TracePoint)

#endif // TRACEPOINT_H
