#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED
#include <vector>
#include "crdtsimNode.h"
#include "crdtsimConnexion.h"
namespace crdtsim
{
class Network
{
public:
    int size () const;
    int createNode ();
    const Node* getNode (int identifier) const;
    bool eraseNode (int identifier);
    bool createConnexion (int sourceIdentifier, int destinationIdentifier);
    bool eraseConnexion (int sourceIdentifier, int destinationIdentifier);
    bool connexionExists (int sourceIdentifier, int destinationIdentifier);

private:
    std::vector<Node> nodes;
    int lastNodeIdentifier{0};
    std::vector<Connexion> connexions;

    void eraseAllConnexionsWithNode (int nodeIdentifier);
};
} //crdtsim
#endif // NETWORK_H_INCLUDED
