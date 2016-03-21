#ifndef CRDTSIMCONNEXION_H_INCLUDED
#define CRDTSIMCONNEXION_H_INCLUDED
namespace crdtsim
{
class Connexion
{
public:
    Connexion (int sourceNodeId, int destinationId);
    int getSourceNodeIdentifier () const;
    int getDestinationNodeIdentifier () const;

private:
    int sourceNodeId, destinationId;
};
} //crdtsim
#endif // CRDTSIMCONNEXION_H_INCLUDED
