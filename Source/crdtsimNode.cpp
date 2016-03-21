#include "crdtsimNode.h"
#include "JuceHeader.h"

namespace crdtsim
{
class TestNode : public juce::UnitTest
{
public:
    TestNode () : juce::UnitTest ("Node") {}
    void runTest ()
    {
        {
            beginTest ("Normal use");
        }
    }
} testTestNode;
}
