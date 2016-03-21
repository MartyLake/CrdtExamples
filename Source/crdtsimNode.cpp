#include "crdtsimNode.h"
#include "JuceHeader.h"
namespace crdtsim
{
Node::Node (int identifier) : identifier (identifier){};
int Node::getIdentifier () const { return identifier; }

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
