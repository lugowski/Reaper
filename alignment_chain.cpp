#include "alignment_chain.h"

Alignment_Chain::Alignment_Chain()
{
}


std::ostream& operator<<(std::ostream& os, const Alignment_Chain& chain)
{
    os << "RT\tMZ\tIntensity" << std::endl;
    for( Alignment_Node node : chain.chain ) {
        os << node.get_rt() << "\t" << node.get_peak().get_mz() << "\t" <<  node.get_peak().get_intensity() << std::endl;
    }
    return os;
}


