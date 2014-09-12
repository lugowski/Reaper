#include "msrun.h"

MSRun::MSRun()
{
}

void MSRun::add_scan( Scan scan )
{
    scans.push_back(scan);
}
