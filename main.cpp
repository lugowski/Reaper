#include <iostream>
#include <string>

#include "msrun.h"
#include "mzxml_reader.h"

int main(int argc, char *argv[])
{
    std::cout << argv[1] << " " << argc << std::endl;
    MzXML_Reader mzxml{argv[1]};
    MSRun ms{ mzxml.read_mzxml() };

    return 0;
}
