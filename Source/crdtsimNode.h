#ifndef CRDTSIMNODE_H_INCLUDED
#define CRDTSIMNODE_H_INCLUDED
#include <memory>
namespace juce
{
class Component;
}
namespace crdtsim
{
class Node
{
public:
    Node (int identifier);
    Node (const Node& nodeToCopy);
    Node (Node&& nodeToMove);
    Node& operator=(const Node& nodeToCopy);
    int getIdentifier () const;
    juce::Component* getComponent () const;

private:
    int identifier;
    std::unique_ptr<juce::Component> component;
};
} //crdtsim
#endif // CRDTSIMNODE_H_INCLUDED
