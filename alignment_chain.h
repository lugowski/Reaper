#ifndef ALIGNMENT_CHAIN_H
#define ALIGNMENT_CHAIN_H

#include <vector>
#include <ostream>
#include <algorithm>

#include "alignment_node.h"

class Alignment_Chain
{
public:
    Alignment_Chain();
    Alignment_Chain& add(Alignment_Node an) { chain.push_back(an); return *this;}
    const Alignment_Node& top() const { return chain[chain.size()-1]; }
    unsigned size() const { return chain.size();}
    friend std::ostream& operator<<(std::ostream& os, const Alignment_Chain& ac);
    double intensity() const
    {
        double intensity{0};
        for (const Alignment_Node& node : chain) {
            intensity = node.get_peak().get_intensity() > intensity ? node.get_peak().get_intensity(): intensity;
        }
        return intensity;
    }
private:
    std::vector<Alignment_Node> chain{};
};

#endif // ALIGNMENT_CHAIN_H
