#include "scan.h"

Scan::Scan(unsigned index, unsigned msLevel, double retention)
    :index{index}, msLevel{msLevel}, retention{retention}
{}

void Scan::read_peaks( QDataStream &data, unsigned num_peaks ){

    for(unsigned i=0; i<num_peaks && data.status() == QDataStream::Ok; ++i) {
        double mz{}, intensity{};
        data >> mz >> intensity;
        peaks.push_back({mz, intensity});
    }

}

unsigned Scan::num_peaks() const
{
    return peaks.size();
}

std::ostream& operator<<(std::ostream& os, const Scan& scan)
{
    for(Peak peak : scan.peaks) {
        os << peak.get_mz() << "\t" << peak.get_intensity() << "\n";
    }
    return os;
}
