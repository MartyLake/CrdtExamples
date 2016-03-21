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
    bool operator==(const Connexion& b) const;
    bool operator!=(const Connexion& b) const;

private:
    int sourceNodeId, destinationId;
};
} //crdtsim
#endif // CRDTSIMCONNEXION_H_INCLUDED
