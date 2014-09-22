#include "scan.h"

#include <algorithm>


Scan::Scan(unsigned index, unsigned msLevel, double retention)
    :index{index}, msLevel{msLevel}, retention{retention}
{}

unsigned Scan::num_peaks() const
{
    return peaks.size();
}

unsigned Scan::get_msLevel() const
{
    return msLevel;
}

unsigned Scan::get_index() const
{
    return index;
}

const Scan& Scan::add_peak( Peak peak )
{
    peaks.push_back(peak);
    return *this;
}

void Scan::centroid()
{
    std::vector<Peak> centroided{};

    //std::cout << *this;

    for (auto p=peaks.cbegin(); p!=peaks.cend(); ++p) {
        if (p == peaks.cbegin() || p == peaks.cend()-1){
            continue;
        }

        if ( ( (p-1)->get_intensity() < p->get_intensity() ) &&
             ( (p+1)->get_intensity() < p->get_intensity() ) ) {

            if ( ( (p-1)->get_intensity() == 0 ) &&
                   ( (p+1)->get_intensity() == 0 ) ) {
                continue; // skip single peaks
            }

            double mz = p->get_mz();

            // find low corner
            auto l=p-1;
            while (l!=peaks.cbegin() && l->get_intensity() &&
                   ( l->get_intensity() < (l+1)->get_intensity() )){
                --l;
            }
            // find high corner
            auto h=p+1;
            while ( h!=peaks.cend() && h->get_intensity() &&
                    ( h->get_intensity() < (h-1)->get_intensity() )){
                ++h;
            }
            // determine triangle area
            double base = h->get_mz() - l->get_mz();
            double intensity = 0.5 * base * p->get_intensity();
            if ( intensity < 0 ) {
                continue; // for ab sciex
            }
            //std::cout << mz << "\t" << intensity << std::endl;
            centroided.push_back( {mz, intensity} );
        }
    }
    peaks.swap(centroided);
    //std::cout << *this;
}

double ppm_error( double x, double y )
{
    return 1E6 * (x-y) / x;
}

double score( const Peak& x, const Peak& y) {
    double error = std::abs(ppm_error(x.get_mz(), y.get_mz()));

    return ((25-error)/25);
}

void Scan::align( Scan other, Alignment& alignment ) const
{
    std::vector<std::vector<double>> map(num_peaks(), std::vector<double>(other.num_peaks(), 0));
    for (unsigned i{}; i<num_peaks(); ++i) {
        for (unsigned j{}; (j<other.num_peaks()) && ( ppm_error(other.peaks[j].get_mz(), peaks[i].get_mz()) < 25); ++j) {
            if( ppm_error(peaks[i].get_mz(), other.peaks[j].get_mz()) > 10 ) {
                continue;
            }
            else {
                double topleft = i == 0 || j == 0 ? 0 : map[i-1][j-1] + score(peaks[i], other.peaks[j]);
                double left = i == 0 ? 0 : map[i-1][j];
                double top = j == 0 ? 0 : map[i][j-1];
                double max = topleft > left && topleft > top ? topleft :
                                                               left > top ? left : top;
                map[i][j] = max;
            }
        }
    }

    //for (unsigned i{}; i<num_peaks(); ++i) {
    //    for (unsigned j{}; j<other.num_peaks(); ++j) {
    //        std::cout << map[i][j] << "\t";
    //    }
    //    std::cout << std::endl;
    //}
    ;
    long j{0};
    for (long i{num_peaks()-1}; i>=0; --i) {
        auto max = std::max_element(map[i].begin(), map[i].end()-j);
        if (*max) {
            j = std::distance(max, map[i].end()) ;
            //alignment[retention].push_back( std::pair<Peak, Peak>{peaks[i], other.peaks[std::distance(map[i].begin(), max)]} );
            //double m1 {peaks[i].get_mz()};
            //double m2 { other.peaks[std::distance(map[i].begin(), max)].get_mz() };

            //mz_map[m1] = m2;
            //alignment[retention] = mz_map;
            //std::cout << msLevel << "\t" << i << "\t" << peaks[i].get_mz() << "\t" << std::distance(map[i].begin(), max) << "\t" << other.peaks[std::distance(map[i].begin(), max)].get_mz() << std::endl;
            alignment.insert({retention, peaks[i]}, {other.retention, other.peaks[std::distance(map[i].begin(), max)]});
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Scan& scan)
{
    os << scan.index << "\t" << scan.msLevel << "\t" << scan.retention << "\n";
    for(const Peak& peak : scan.peaks) {
        os << peak.get_mz() << "\t" << peak.get_intensity() << "\n";
    }
    return os;
}
