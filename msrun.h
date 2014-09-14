#ifndef MSRUN_H
#define MSRUN_H

#include <vector>
#include <string>
#include <stdexcept>

#include "scan.h"

class MSRunException : std::runtime_error
{
public:
    MSRunException(const std::string& error)
        :std::runtime_error(error)
    {}
};

class MSRun
{
public:
    MSRun();
    void add_scan( Scan scan );
    void centroid( unsigned level );
    void print_scan( unsigned scan );
    std::map<unsigned, std::vector<std::pair<Peak, Peak>>> align( unsigned level );
private:
    std::vector<Scan> scans{};
};

#endif // MSRUN_H
