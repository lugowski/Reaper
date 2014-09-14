#include <iostream>
#include <string>

#include "msrun.h"
#include "mzxml_reader.h"

int main(int argc, char *argv[])
{
    //std::cout << "Reading: " << argv[1] << std::endl;
    MzXML_Reader mzxml{argv[1]};
    MSRun ms{ mzxml.read_mzxml() };
    //ms.print_scan(0);
    //std::cout << "Centroiding: " << argv[1] << std::endl;
    ms.centroid(1);
    std::map<unsigned, std::vector<std::pair<Peak, Peak>>> alignment = ms.align(1);
    for( auto a : alignment) {
        std::cout << a.first << "\t" << a.second.size() << std::endl;
    }

    return 0;
}
