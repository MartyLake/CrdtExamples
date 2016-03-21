#include "crdtsimNetwork.h"
#include "JuceHeader.h"

namespace crdtsim
{
int Network::size () const { return nodes.size (); }
int Network::createNode ()
{
    auto newNode = Node{lastNodeIdentifier++};
    nodes.push_back (newNode);
    jassert (size () > 0);
    return nodes.back ().getIdentifier ();
}

class TestNetwork : public juce::UnitTest
{
public:
    TestNetwork () : juce::UnitTest ("Network") {}
    void runTest ()
    {
        {
            beginTest ("Network is empty at creation.");
            Network network;
            expectEquals (network.size (), 0);
        }
        {
            beginTest ("Network can create nodes.");
            Network network;
            network.createNode ();
            network.createNode ();
            expectEquals (network.size (), 2);
        }
    }
} testTestNetwork;
}
