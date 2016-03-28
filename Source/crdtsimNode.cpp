#include "crdtsimNode.h"
#include "JuceHeader.h"
namespace crdtsim
{
Node::Node (int identifier) : identifier (identifier)
{
    component.reset (new juce::TextButton ());
    auto textButton = static_cast<TextButton*> (getComponent ());
    textButton->setButtonText ("Node #" + std::to_string (identifier));
};
Node::Node (Node&& nodeToMove) : Node (nodeToMove.identifier)
{
    auto parent = nodeToMove.component->getParentComponent ();
    if (nullptr != parent)
    {
        parent->addAndMakeVisible (component.get ());
    }
}
Node::Node (const Node& nodeToCopy) : Node (nodeToCopy.identifier)
{
    auto parent = nodeToCopy.component->getParentComponent ();
    if (nullptr != parent)
    {
        parent->addAndMakeVisible (component.get ());
    }
}
Node& Node::operator=(const Node& nodeToCopy)
{
    //std::swap (*this, nodeToCopy);
    auto parent = component->getParentComponent();
    if (nullptr != parent) {
        parent->removeChildComponent(component.get());
    }
    identifier = nodeToCopy.identifier;
    //????????????
    return *this;
}
int Node::getIdentifier () const { return identifier; }
juce::Component* Node::getComponent () const
{
    return component.get ();
}

class TestNode : public juce::UnitTest
{
public:
    TestNode () : juce::UnitTest ("Node") {}
    void runTest ()
    {
        {
            beginTest ("Store and retrieve identifier");
            auto identifier = juce::UnitTest::getRandom ().nextInt ();
            Node n{identifier};
            expectEquals (n.getIdentifier (), identifier);
        }
    }
} testTestNode;
}
