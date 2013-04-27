#include "qreadgpx.h"

#include <QtXml/QXmlSimpleReader>

class GPXDataContentHandler: QXmlContentHandler {
private :
    TraceData data;

public:
    virtual bool startElement( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts ) {
        int i;
        if(qName == "trk") {
            qWarning("track found : ");
            for(i=0; i< atts.length(); i++)
                qWarning("%s:%s", atts.qName(i), atts.value(i));
        }
    }
};


QReadGPX::QReadGPX()
{
}

TraceData * QReadGPX::parseData(QIODevice data) {
    QXmlSimpleReader xmlReader = new QXmlSimpleReader();
    QXmlInputSource dataSource = new QXmlInputSource(data);
    bool ret;

    if(! dataSource) {
        cout << "Impossible de lire la source de données demandée" <<endl;
    }
    QXmlContentHandler hdl = new QXmlContentHandler()
    xmlReader.setContentHandler
    ret = xmlReader.parse(dataSource);
    if(! ret) {
        cout << "Impossible de parser la source de données XML" << endl;
    }
}
