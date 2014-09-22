#ifndef ALIGNMENT_NODE_H
#define ALIGNMENT_NODE_H

#include <utility>

#include "peak.h"

class Alignment_Node
{
public:
    Alignment_Node();
    Alignment_Node(double rt, Peak peak): rt{rt}, peak{peak} {}
    double get_rt() const { return rt; }
    const Peak& get_peak() const { return peak; }
private:
    double rt{};
    Peak peak{};
};

#endif // ALIGNMENT_NODE_H
