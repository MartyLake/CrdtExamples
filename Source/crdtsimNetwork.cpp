#include "crdtsimNetwork.h"
#include "JuceHeader.h"

namespace crdtsim
{
int Network::size () const { return 0; }

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
    }
} testTestNetwork;
}
