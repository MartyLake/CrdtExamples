#include "crdtsimNetwork.h"
#include "JuceHeader.h"
#include <algorithm>

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
const Node* Network::getNode (int identifier) const
{
    auto sameIdentifierPredicate = [identifier](const Node& node)
    {
        return node.getIdentifier () == identifier;
    };
    auto foundNode = std::find_if (std::begin (nodes), std::end (nodes), sameIdentifierPredicate);
    if (foundNode == std::end (nodes))
    {
        juce::Logger::getCurrentLogger ()->outputDebugString ("Network::getNode(" + std::to_string (identifier) + ") can't find Node with specified Id.");
        return nullptr;
    }
    return &*foundNode;
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
        {
            beginTest ("Network can store nodes that can be retrieved by their IDs.");
            Network network;
            auto nodeIdentifier = network.createNode ();
            auto retrievedNode = network.getNode (nodeIdentifier);
            expect (retrievedNode != nullptr);
            expectEquals (retrievedNode->getIdentifier (), nodeIdentifier);
        }
        {
            beginTest ("Network return nullptr when trying to retrieved an invaled ID.");
            Network network;
            auto nodeIdentifier1 = juce::UnitTest::getRandom ().nextInt ();
            auto retrievedNode = network.getNode (nodeIdentifier1);
            expect (retrievedNode == nullptr, "Empty network returned non empty node ptr when asked for Identifier(" + std::to_string (nodeIdentifier1) + ")");
        }
    }
} testTestNetwork;
}
