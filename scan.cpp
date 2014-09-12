#include "scan.h"

Scan::Scan(unsigned index, unsigned msLevel, double retention)
    :index{index}, msLevel{msLevel}, retention{retention}
{}

unsigned Scan::num_peaks() const
{
    return peaks.size();
}
