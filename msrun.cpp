#include "msrun.h"

#include <iostream>

MSRun::MSRun()
{
}

void MSRun::add_scan( Scan scan )
{
    scans.push_back(scan);
}

void MSRun::centroid(unsigned level)
{
    for ( auto& scan : scans ) {
        if (scan.get_msLevel() == level) {
            scan.centroid();
        }
    }
}

void MSRun::print_scan( unsigned scan )
{
    for( Scan& s : scans ) {
        if(s.get_index()==scan){
            std::cout << s;
            return;
        }
    }
}

Alignment MSRun::align( unsigned level )
{
    Alignment alignment{};
    // find last spectra of desired ms level
    auto last = scans.cend();
    while ( ( last != scans.cbegin() ) && (last->get_msLevel() != level) ) {
        --last;
    }
    // loop over consecutive pairs of spectra at the same msLevel and align them
    for( auto scan = scans.cbegin(); scan != last; ++scan ) {
        //if (scan->get_index() != 1) throw scan; // remove after testing
        if (scan->get_msLevel() != level) {
            continue;
        }
        if (scan->get_index() < 1000) { continue; };
        if (scan->get_index() > 1250) { break; };
        // find the adjacent same level spectra
        auto next = scan+1;
        while ( ( next != last ) && (next->get_msLevel() != level) ) {
            ++next;
        }
        scan->align( *next, alignment );
    }
    return alignment;
}
