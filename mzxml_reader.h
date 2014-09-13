#ifndef MZXML_READER_H
#define MZXML_READER_H

#include <stdexcept>
#include <string>

#include <QFile>
#include <QXmlStreamReader>
#include <QString>
#include <QDataStream>


#include "scan.h"
#include "msrun.h"

class MzXMLException : std::runtime_error
{
public:
    MzXMLException(std::string const& error)
        :std::runtime_error(error)
    {}
};

class MzXML_Reader
{
public:
    MzXML_Reader( QString filename );
    MSRun read_mzxml();
private:
    void parse_peaks( Scan& scan, unsigned num_peaks );
    Scan parse_scan();

    QFile file;
    QXmlStreamReader xml{};

    // mzxml string constants
    const static QString PEAKS;
    static const QString SCAN;
    static const QString PRECISION;
    static const QString BYTEORDER;
    static const QString PEAKS_COUNT;
    static const QString INDEX;
    static const QString MSLEVEL;
    static const QString RETENTION;

    // map mzxml precision strings to QT constants
    std::map<QString, decltype(QDataStream::SinglePrecision)> to_precision{
        { "32", QDataStream::SinglePrecision},
        { "64", QDataStream::DoublePrecision},
    };
    // map mzxml byteorder strings to QT constants
    std::map<QString, decltype(QDataStream::BigEndian)> to_byteorder{
        { "network", QDataStream::BigEndian},
        { "host", QDataStream::LittleEndian},
    };
};

#endif // MZXML_READER_H
