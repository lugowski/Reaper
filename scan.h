#ifndef SCAN_H
#define SCAN_H

#include <vector>
#include <stdexcept>
#include <ostream>

#include <QDataStream>

#include "peak.h"

class ScanException : public std::runtime_error
{
public:
    ScanException(const std::string& error)
        :std::runtime_error(error)
    {}
};

class Scan
{
public:
    Scan(unsigned index, unsigned msLevel, double retention);
    const Scan& add_peak( Peak peak );
    unsigned num_peaks() const;
    unsigned get_msLevel() const;
    unsigned get_index() const;
    void centroid();
    void align( Scan other, std::map<unsigned, std::vector<std::pair<Peak, Peak>>>& aligned ) const;
    friend std::ostream& operator<<(std::ostream& os, const Scan& scan);
private:
    unsigned index;
    unsigned msLevel;
    double retention;
    std::vector<Peak> peaks{};
};

#endif // SCAN_H
