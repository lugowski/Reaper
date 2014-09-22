#include <iostream>
#include <map>
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
    //std::map<double, std::map<double, double>> alignment = ms.align(1);
    Alignment alignment = ms.align(1);
    alignment.print_all();
    //auto low = alignment.begin();
    //auto mz = low->second.begin();
    //std::cout << "RT\tMZ\tnext" << std::endl;
    //while(1){
    //    std::cout << low->first << "\t" << mz->first << "\t" << mz->second << std::endl;
    //    ++low;
    //    mz = low->second.find(mz->second);
    //    if (mz == low->second.end()) {
    //        break;
    //    }
    //}


    return 0;
}
