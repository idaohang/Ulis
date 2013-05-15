#include "simplegpxreader.h"
#include <QtXml/QXmlSimpleReader>
#include <QtDebug>
#include <QDateTime>

class GPXDataContentHandler: public QXmlDefaultHandler {
private :
    bool onTrk;
    bool onTrkSeg;
    bool onTrkSegPt;

    TracePoint  cur_pt;
    Segment     * cur_seg;
    Track       * cur_trk;

    QString tmp;

    Trace* all_track;

public:

    Trace* getComputedTrace() {
        return all_track;
    }

    virtual bool fatalError(const QXmlParseException &exception) {
        qWarning() << "Fatal error on line" << exception.lineNumber()
                   << ", column" << exception.columnNumber() << ":"
                   << exception.message();
        return false;
    }

    /**
     * @brief First callback while parsing the data
     *
     * prepare the state machine to handle the data
     *
     */
    virtual bool startDocument() {
        this->onTrk      = false;
        this->onTrkSeg   = false;
        this->onTrkSegPt = false;
        all_track = new Trace();
        return true;
    }

    virtual bool characters(const QString &ch) {
        this->tmp.append(ch);
        return true;
    }

    virtual bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName) {

        // End of the "main" node : track, segment, or point
        if(qName =="trk") {
            this->all_track->add(this->cur_trk);
            this->onTrk = false;
        } else if(qName == "trkseg") {
            this->cur_trk->add(this->cur_seg);
            this->onTrkSeg = false;
        } else if(qName == "trkpt") {
            this->cur_seg->add(this->cur_pt);
            this->onTrkSegPt = false;
        }

        // End of secondary nodes (comments, name) :
        if(qName == "cmt") {
            if(this->onTrkSeg) cur_seg->setDescription(this->tmp);
            else if(this->onTrk) cur_trk->setDescription(this->tmp);
        }
        else if(qName == "name") {
            if      (this->onTrkSeg) cur_seg->setName(this->tmp);
            else if (this->onTrk) cur_trk->setName(this->tmp);
        }

        // End of data for the points :
        if(this->onTrkSegPt) {
            if(qName =="ele")           this->cur_pt.alt = this->tmp.toDouble();
            else if(qName =="time")     this->cur_pt.time = QDateTime::fromString(this->tmp, Qt::ISODate);
        }

        return true;
    }


    /**
     * @brief setElement<double> populate the variable var with a double from att
     * @param var
     * @param att
     * @param nameElt
     * @return
     */
    bool setElementDouble(double& var, QXmlAttributes att, QString nameElt) {
        bool isOk;
        QString stringValue;
        stringValue = att.value(nameElt);
        Q_ASSERT(stringValue != "");
        var = stringValue.toDouble(&isOk);
        Q_ASSERT(isOk);
        return isOk;
    }

    virtual bool startElement( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts ) {
        this->tmp = "";

        if(qName == "trk") {
            this->onTrk = true;
            this->cur_trk = new Track();
        } else if(qName == "trkseg") {
            this->onTrkSeg = true;
            this->cur_seg = new Segment();
        } else if(qName == "trkpt") {
            this->onTrkSegPt = true;
            this->cur_pt = TracePoint();
            setElementDouble(this->cur_pt.lat, atts, "lat");
            setElementDouble(this->cur_pt.lon, atts, "lon");
        }
        return true;
    }
};


Trace* SimpleGPXReader::parseData(QIODevice * data) {

    Trace* tmpTrace = new Trace();

    QXmlSimpleReader * xmlReader  = new QXmlSimpleReader();
    QXmlInputSource  * dataSource = new QXmlInputSource(data);
    bool ret;

    qDebug() << "Début du parse des données XML";

    if(! dataSource) {
        qWarning() << "Impossible de lire la source de données demandée";
    }

    GPXDataContentHandler * hdl = new GPXDataContentHandler();
    xmlReader->setContentHandler(hdl);
    ret = xmlReader->parse(dataSource);

    if(! ret) {
        qWarning() << "Impossible de parser la source de données XML";
    }

    tmpTrace = hdl->getComputedTrace();

    qDebug() <<"Nombre de points trouvés :" << tmpTrace->length();

    return tmpTrace;
}

SimpleGPXReader::SimpleGPXReader()
{
}
