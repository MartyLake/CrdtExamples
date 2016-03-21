#include "crdtsimConnexion.h"
#include "JuceHeader.h"

namespace crdtsim
{
class TestConnexion : public juce::UnitTest
{
public:
    TestConnexion () : juce::UnitTest ("Connexion") {}
    void runTest ()
    {
        {
            beginTest ("Normal use");
        }
    }
} testTestConnexion;
}
