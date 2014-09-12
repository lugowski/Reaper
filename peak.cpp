#include "peak.h"

bool valid( const Peak &p) {
    return ( p.get_mz() > 0 && p.get_intensity() > 0 );
}

Peak::Peak(double mz, double intensity)
    :mz{mz},intensity{intensity}
{
    if (!valid(*this) )
    {
        throw PeakException{"Invalid peak"};
    }
}

inline double Peak::get_mz() const
{
    return mz;
}

inline double Peak::get_intensity() const
{
    return intensity;
}
