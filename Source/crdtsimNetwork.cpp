#include "crdtsimNetwork.h"
#include "JuceHeader.h"

namespace crdtsim
{
class TestNetwork : public juce::UnitTest
{
public:
    TestNetwork () : juce::UnitTest ("Network") {}
    void runTest ()
    {
        {
            beginTest ("Normal use");
        }
    }
} testTestNetwork;
}
