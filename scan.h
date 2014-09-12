#ifndef SCAN_H
#define SCAN_H

#include <vector>

#include "peak.h"

class Scan
{
public:
    Scan(unsigned index, unsigned msLevel, double retention);
    unsigned num_peaks() const;
private:
    unsigned index;
    unsigned msLevel;
    double retention;
    std::vector<Peak> peaks{};
};

#endif // SCAN_H
