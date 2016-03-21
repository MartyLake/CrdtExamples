#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED
#include <vector>
#include "crdtsimNode.h"
namespace crdtsim
{
class Network
{
public:
    int size () const;
    int createNode ();

private:
    std::vector<Node> nodes;
    int lastNodeIdentifier{0};
};
} //crdtsim
#endif // NETWORK_H_INCLUDED
