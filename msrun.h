#ifndef MSRUN_H
#define MSRUN_H

#include <vector>
#include <string>

#include "scan.h"

class MSRun
{
public:
    MSRun();
    void add_scan( Scan scan );
private:
    std::vector<Scan> scans{};
};

#endif // MSRUN_H
