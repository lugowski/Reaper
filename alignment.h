#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "alignment_chain.h"
#include "alignment_node.h"

struct same_as {
    same_as(Alignment_Node node): node{node} {}
    bool operator()(const Alignment_Chain& chain) {
        const Alignment_Node& other = chain.top();
        return ( other.get_rt() == node.get_rt())
                && ( other.get_peak().get_mz() == node.get_peak().get_mz());
    }
private:
    Alignment_Node node;
};

class Alignment
{
public:
    Alignment();
    Alignment& insert(Alignment_Node old, Alignment_Node node)
    {
        same_as current{old};
        auto found = std::find_if(alignment.begin(), alignment.end(), current);
        if (found == alignment.end()) {
            Alignment_Chain ac{};
            ac.add(old);
            ac.add(node);
            alignment.push_back(ac);
        }
        else {
            found->add(node);
        }
        return *this;
    }
    void print_longest(){
        std::vector<int> sizes{};
        for( auto &chain : alignment) {
            sizes.push_back(chain.intensity());
        }

        auto max = std::max_element(sizes.begin(), sizes.end());
        int index = std::distance(sizes.begin(), max);

        Alignment_Chain ac = alignment[index];
        std::cout << ac;
    }

    void print_all() {
        std::cout << alignment.size() << std::endl;
        for (unsigned i = 0; i<alignment.size(); ++i) {
            //if (alignment[i].intensity() < 50 ) {
            //    std::cout << "Skipping " + std::to_string(i) << std::endl;
            //    continue;
            //}
            std::ofstream myfile;
            myfile.open(std::to_string(i));
            myfile << alignment[i];
            myfile.close();
        }

    }

private:
    std::vector<Alignment_Chain> alignment{};
};

#endif // ALIGNMENT_H
