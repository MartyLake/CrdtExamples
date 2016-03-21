#ifndef CRDTSIMNODE_H_INCLUDED
#define CRDTSIMNODE_H_INCLUDED
namespace crdtsim
{
class Node
{
public:
    Node (int identifier);
    int getIdentifier () const;

private:
    int identifier;
};
} //crdtsim
#endif // CRDTSIMNODE_H_INCLUDED
