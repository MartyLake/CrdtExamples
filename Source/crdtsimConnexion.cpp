#include "crdtsimConnexion.h"
#include "JuceHeader.h"

namespace crdtsim
{
Connexion::Connexion (int sourceNodeId, int destinationId) : sourceNodeId (sourceNodeId), destinationId (destinationId) {}
int Connexion::getSourceNodeIdentifier () const { return sourceNodeId; }
int Connexion::getDestinationNodeIdentifier () const { return destinationId; }

bool Connexion::operator==(const Connexion& b) const
{
    return (getSourceNodeIdentifier () == b.getSourceNodeIdentifier ()) &&
           (getDestinationNodeIdentifier () == b.getDestinationNodeIdentifier ());
}
bool Connexion::operator!=(const Connexion& b) const
{
    return !(*this == b);
}

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
        {
            beginTest ("Operator equality and difference overload");
            auto random = juce::UnitTest::getRandom ();
            auto nodeIdentifier1 = random.nextInt ();
            auto nodeIdentifier2 = random.nextInt ();
            while (nodeIdentifier1 == nodeIdentifier2)
            {
                nodeIdentifier2 = random.nextInt ();
            }
            expect (nodeIdentifier2 != nodeIdentifier1, "Bad initial conditions");
            auto nodeIdentifier3 = random.nextInt ();
            while (nodeIdentifier1 == nodeIdentifier3 && nodeIdentifier2 == nodeIdentifier3)
            {
                nodeIdentifier3 = random.nextInt ();
            }
            expect (nodeIdentifier3 != nodeIdentifier1, "Bad initial conditions");
            expect (nodeIdentifier2 != nodeIdentifier3, "Bad initial conditions");
            Connexion connexion12{nodeIdentifier1, nodeIdentifier2};
            Connexion connexion12bis{connexion12};
            Connexion connexion13{nodeIdentifier1, nodeIdentifier3};
            expect (connexion12 == connexion12);
            expect (connexion12 == connexion12bis);
            expect (!(connexion12 == connexion13));
            expect (!(connexion12 != connexion12));
            expect (!(connexion12 != connexion12bis));
            expect (connexion12 != connexion13);
        }
    }
} testTestConnexion;
}
