#include "crdtsimConnexion.h"
#include "JuceHeader.h"

namespace crdtsim
{
Connexion::Connexion (int sourceNodeId, int destinationId) : sourceNodeId (sourceNodeId), destinationId (destinationId) {}
int Connexion::getSourceNodeIdentifier () const { return sourceNodeId; }
int Connexion::getDestinationNodeIdentifier () const { return destinationId; }

class TestConnexion : public juce::UnitTest
{
public:
    TestConnexion () : juce::UnitTest ("Connexion") {}
    void runTest ()
    {
        {
            beginTest ("Create a connexion from node1 to node2");
            auto random = juce::UnitTest::getRandom ();
            auto nodeIdentifier1 = random.nextInt ();
            auto nodeIdentifier2 = random.nextInt ();
            while (nodeIdentifier1 == nodeIdentifier2)
            {
                nodeIdentifier2 = random.nextInt ();
            }
            expect (nodeIdentifier2 != nodeIdentifier1, "Bad initial conditions");
            Connexion connexion{nodeIdentifier1, nodeIdentifier2};
            expectEquals (connexion.getSourceNodeIdentifier (), nodeIdentifier1);
            expectEquals (connexion.getDestinationNodeIdentifier (), nodeIdentifier2);
        }
    }
} testTestConnexion;
}
