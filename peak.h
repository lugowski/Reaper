#ifndef PEAK_H
#define PEAK_H

#include <string>
#include <stdexcept>

class PeakException : std::runtime_error
{
public:
    PeakException(const std::string& error)
        :std::runtime_error(error)
    {}
};

class Peak
{
public:
    Peak(){}
    Peak(double mz, double intensity);
    double get_mz() const;
    double get_intensity() const;
private:
    double mz{};
    double intensity{};
};

bool operator==(Peak& p1, Peak& p2);
bool operator!=(Peak& p1, Peak& p2);

#endif // PEAK_H
