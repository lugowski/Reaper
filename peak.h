#ifndef PEAK_H
#define PEAK_H

#include <string>
#include <stdexcept>

class PeakException : std::runtime_error
{
public:
    PeakException(std::string const& error)
        :std::runtime_error(error)
    {}
};

class Peak
{
public:
    Peak(double mz, double intensity);
    double get_mz() const;
    double get_intensity() const;
private:
    const double mz;
    const double intensity;
};

#endif // PEAK_H
