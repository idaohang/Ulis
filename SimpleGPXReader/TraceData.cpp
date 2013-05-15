#include "TraceData.h"

/* Anonymous namespace, unavailable from other files */
namespace {
    /* Preliminary checks before trying every item of the container */
    template <typename T>
    bool preliminaryTests(T * t1, T * t2) {
        bool isEq = true;
        if(t1->length() != t2->length()) {
            isEq = false;
        } else if(t1->description() != t2->description()) {
            isEq = false;
        } else if(t1->name() != t2->name() ) {
            isEq = false;
        }
        return isEq;
    }

    /* Verify every object inside the container, assuming the items can be dereferenced */
    template <typename InputIterator1, typename InputIterator2>
    inline bool qEqualPointer(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
            if (!(*(*first1) == *(*first2)) )
                return false;
        return true;
    }
}

bool TracePoint::operator==(const TracePoint& t) const {
    bool isEq = true;
    isEq = (this->lon == t.lon && \
           this->lat == t.lat && \
           this->alt == t.alt && \
           this->time == t.time);
    return isEq;
}

void Trace::add(Track* newElt) {
    Node_Template::add(newElt);
    emit elementAdded();
}

Track* Trace::pop(int index) {
    Track* p = Node_Template::pop(index);
    emit elementRemoved(index);
    return p;
}

void Trace::change(int index, Track* elt) {
    Node_Template::change(index, elt);
    emit elementChanged(index);
}

Trace::~Trace() {
    qDeleteAll(this->m_elements);
}

void Track::add(Segment* newElt) {
    Node_Template::add(newElt);
    emit elementAdded();
}

Segment* Track::pop(int index) {
    Segment* p = Node_Template::pop(index);
    emit elementRemoved(index);
    return p;
}

void Track::change(int index, Segment* elt) {
    Node_Template::change(index, elt);
    emit elementChanged(index);
}

Track::~Track() {
    qDeleteAll(this->m_elements);
}

void Segment::add(TracePoint newElt) {
    Node_Template::add(newElt);
    emit elementAdded();
}

TracePoint Segment::pop(int index) {
    TracePoint p = Node_Template::pop(index);
    emit elementRemoved(index);
    return p;
}

void Segment::change(int index, TracePoint elt) {
    Node_Template::change(index, elt);
    emit elementChanged(index);
}

bool Segment::operator==(const Segment &t1) const {
    bool isEq = true;
    if(preliminaryTests(this, &t1)) {
        isEq = qEqual(t1.m_elements.begin(), t1.m_elements.end(), this->m_elements.begin());
    } else {
        isEq = false;
    }
    return isEq;
}

bool Trace::operator==(const Trace &t1) const {
    bool isEq = true;
    if(preliminaryTests(this, &t1)) {
        isEq = qEqualPointer(t1.m_elements.begin(), t1.m_elements.end(), this->m_elements.begin());
    } else {
        isEq = false;
    }
    return isEq;
}

bool Track::operator==(const Track &t1) const {
    bool isEq = true;
    if(preliminaryTests(this, &t1)) {
        isEq = qEqualPointer(t1.m_elements.begin(), t1.m_elements.end(), this->m_elements.begin());
    } else {
        isEq = false;
    }
    return isEq;

}




QDebug operator <<(QDebug dbg, const TracePoint& Obj)
{
    dbg << "lon:" << Obj.lon << " lat:" << Obj.lat <<" ";
    dbg << "alt:" << Obj.alt << " time" << Obj.time;
    return dbg.space();
}
