#include "mzxml_reader.h"

#include <QIODevice>
#include <QByteArray>
#include <QRegExp>

double extract_time( const QString& s )
{
    static QRegExp rx{"PT([^S]+)S"};
    if (rx.exactMatch(s)) {
        return rx.cap(1).toDouble();
    } else {
        throw MzXMLException{"Invalid retention time"};
    }
}

void MzXML_Reader::parse_peaks( Scan &scan, unsigned num_peaks )
{
    while (xml.qualifiedName().compare(PEAKS)!=0 || !xml.isEndElement() )
    {
        xml.readNext();

        // get precision and byte order from xml attributes
        decltype(QDataStream::SinglePrecision) precision{
            to_precision[ xml.attributes().value(PRECISION).toString() ]
        };
        decltype(QDataStream::BigEndian) byte_order{
            to_byteorder[ xml.attributes().value(BYTEORDER).toString() ]
        };

        // convert base64 encoded peak list to floating point and store
        QDataStream data{ QByteArray::fromBase64(xml.text().toLocal8Bit()) };
        data.setFloatingPointPrecision(precision);
        data.setByteOrder(byte_order);
        scan.read_peaks(data, num_peaks);
    }
}

Scan MzXML_Reader::parse_scan()
{
    unsigned index{xml.attributes().value(INDEX).toUInt()};
    unsigned msLevel{xml.attributes().value(MSLEVEL).toUInt()};
    unsigned num_peaks{xml.attributes().value(PEAKS_COUNT).toUInt()};
    double retention{extract_time(xml.attributes().value(RETENTION).toString())};
    Scan scan{index, msLevel, retention};

    while (xml.qualifiedName().compare(SCAN)!=0 || !xml.isEndElement() )
    {
        xml.readNext();
        if (xml.qualifiedName().compare(PEAKS) == 0) {
            parse_peaks( scan, num_peaks);
        }
    }
    return scan;
}

MSRun MzXML_Reader::read_mzxml()
{
    MSRun ms{};
    while ( !xml.atEnd() ) {
        xml.readNext();
        if (xml.qualifiedName().compare(SCAN) == 0) {
            ms.add_scan( parse_scan() );
        }
    }
    return ms;
}

MzXML_Reader::MzXML_Reader( QString filename )
    :file{filename}
{
    if(!file.open(QIODevice::ReadOnly)) {
        throw MzXMLException{ file.errorString().toUtf8().constData() };
    }
    xml.setDevice(&file);
}

const QString MzXML_Reader::PEAKS{"peaks"};
const QString MzXML_Reader::SCAN{"scan"};
const QString MzXML_Reader::PRECISION{"precision"};
const QString MzXML_Reader::BYTEORDER{"byteOrder"};
const QString MzXML_Reader::PEAKS_COUNT{"peaksCount"};
const QString MzXML_Reader::INDEX{"num"};
const QString MzXML_Reader::MSLEVEL{"num"};
const QString MzXML_Reader::RETENTION{"retentionTime"};
