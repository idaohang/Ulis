#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QtAlgorithms>
class Node_QT: public QObject {
    Q_OBJECT
    signals:
        void elementAdded();
        void elementRemoved(int index);
        void elementChanged(int index);

};

template <class T>
class Node_Template {
    public:
        void setDescription(QString  desc) { this->m_description = desc; }
        QString description() const { return this->m_description; }
        void setName(QString name) { this->m_name = name; }
        QString name() const { return this->m_name; }
        void add(T newElt) { this->m_elements.append(newElt); }
        T pop(int index) { T p = this->m_elements[index]; this->m_elements.removeAt(index); return p; }
        void change(int index, T elt) { this->m_elements[index] = elt; }
        int length() const { return this->m_elements.length(); }
        const T & operator[](int index) const { return this->m_elements[index]; }
//        virtual bool operator==(const Node_Template<T> &t1) { return qEqual(t1.m_elements.begin(), t1.m_elements.end(), this->m_elements.begin()); }
//        bool operator!=(const Node_Template<T> &t1) const { return !(*this == t1); }

    protected:
        QString  m_description;
        QString  m_name;
        QList<T> m_elements;
};

#endif // NODE_H
