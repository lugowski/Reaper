#ifndef SCAN_H
#define SCAN_H

#include <vector>
#include <stdexcept>
#include <ostream>

#include <QDataStream>

#include "peak.h"

class ScanException : std::runtime_error
{
public:
    ScanException(std::string const& error)
        :std::runtime_error(error)
    {}
};

class Scan
{
public:
    Scan(unsigned index, unsigned msLevel, double retention);
    void read_peaks( QDataStream &data , unsigned num_peaks);
    unsigned num_peaks() const;
    friend std::ostream& operator<<(std::ostream& os, const Scan& scan);
private:
    unsigned index;
    unsigned msLevel;
    double retention;
    std::vector<Peak> peaks{};
};

#endif // SCAN_H
