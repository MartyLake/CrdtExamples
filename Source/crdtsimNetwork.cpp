#include "crdtsimNetwork.h"
#include <algorithm>

namespace crdtsim
{
Network::Network () : valueTree ("RootNetwork") {}
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
bool Network::eraseNode (int identifier)
{
    auto sameIdentifierPredicate = [identifier](const Node& node)
    {
        return node.getIdentifier () == identifier;
    };
    auto nodeToRemodeIt = std::remove_if (std::begin (nodes), std::end (nodes), sameIdentifierPredicate);
    if (nodeToRemodeIt == std::end (nodes))
    {
        juce::Logger::getCurrentLogger ()->outputDebugString ("Network::eraseNode(" + std::to_string (identifier) + ") can't find Node with specified Id.");
        return false;
    }
    nodes.erase (nodeToRemodeIt, std::end (nodes));
    eraseAllConnexionsWithNode (identifier);
    return true;
}
bool Network::createConnexion (int sourceIdentifier, int destinationIdentifier)
{
    if (sourceIdentifier == destinationIdentifier)
    {
        juce::Logger::getCurrentLogger ()->outputDebugString ("Network::createConnexion(" + std::to_string (sourceIdentifier) + "," + std::to_string (destinationIdentifier) + ") can't create Connexion with sourceIdentifier equals destinationIdentifier.");
        return false;
    }
    if (getNode (sourceIdentifier) == nullptr)
    {
        juce::Logger::getCurrentLogger ()->outputDebugString ("Network::createConnexion(" + std::to_string (sourceIdentifier) + "," + std::to_string (destinationIdentifier) + ") can't create Connexion with sourceIdentifier not refering to an existing node.");
        return false;
    }
    if (getNode (destinationIdentifier) == nullptr)
    {
        juce::Logger::getCurrentLogger ()->outputDebugString ("Network::createConnexion(" + std::to_string (sourceIdentifier) + "," + std::to_string (destinationIdentifier) + ") can't create Connexion with destinationIdentifier not refering to an existing node.");
        return false;
    }

    auto connexionToAdd = Connexion{sourceIdentifier, destinationIdentifier};
    if (std::find (std::begin (connexions), std::end (connexions), connexionToAdd) == std::end (connexions))
    {
        connexions.push_back (connexionToAdd);
    }
    return true;
}
bool Network::eraseConnexion (int sourceIdentifier, int destinationIdentifier)
{
    auto connexionToDelete = Connexion{sourceIdentifier, destinationIdentifier};
    auto findResult = std::find (std::begin (connexions), std::end (connexions), connexionToDelete);
    if (findResult == std::end (connexions))
    {
        juce::Logger::getCurrentLogger ()->outputDebugString ("Network::eraseConnexion(" + std::to_string (sourceIdentifier) + "," + std::to_string (destinationIdentifier) + ") can't find Connexion to delete.");
        return false;
    }
    connexions.erase (findResult);
    return true;
}
bool Network::connexionExists (int sourceIdentifier, int destinationIdentifier)
{
    auto connexionToFind = Connexion{sourceIdentifier, destinationIdentifier};
    auto findResult = std::find (std::begin (connexions), std::end (connexions), connexionToFind);
    return findResult != std::end (connexions);
}
void Network::eraseAllConnexionsWithNode (int nodeIdentifier)
{
    auto sameSourcePredicate = [nodeIdentifier](const Connexion& c)
    {
        return c.getSourceNodeIdentifier () == nodeIdentifier;
    };
    connexions.erase (std::remove_if (std::begin (connexions), std::end (connexions), sameSourcePredicate), std::end (connexions));
    auto sameDestinationPredicate = [nodeIdentifier](const Connexion& c)
    {
        return c.getDestinationNodeIdentifier () == nodeIdentifier;
    };
    connexions.erase (std::remove_if (std::begin (connexions), std::end (connexions), sameDestinationPredicate), std::end (connexions));
}
juce::ValueTree& Network::getValueTree ()
{
    return valueTree;
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
        {
            beginTest ("Network can delete a node with the specified ID.");
            Network network;
            auto nodeIdentifier1 = network.createNode ();
            expectEquals (network.size (), 1);
            auto succesfullyDeleted = network.eraseNode (nodeIdentifier1);
            expectEquals (network.size (), 0);
            expect (succesfullyDeleted);
        }
        {
            beginTest ("Network returns false when asked to delete a node with an invalid ID.");
            Network network;
            auto nodeIdentifier1 = juce::UnitTest::getRandom ().nextInt ();
            expectEquals (network.size (), 0);
            auto succesfullyDeleted = network.eraseNode (nodeIdentifier1);
            expect (!succesfullyDeleted);
        }
        {
            beginTest ("Network returns true when asked to create a connexion between two valid different identifier.");
            Network network;
            auto nodeIdentifier1 = network.createNode ();
            auto nodeIdentifier2 = network.createNode ();
            auto creationResult = network.createConnexion (nodeIdentifier1, nodeIdentifier2);
            expect (creationResult);
        }
        {
            beginTest ("Network returns false when asked to create a connexion with sourceIdentifier equals destinationIdentifier.");
            Network network;
            auto nodeIdentifier1 = network.createNode ();
            auto creationResult = network.createConnexion (nodeIdentifier1, nodeIdentifier1);
            expect (!creationResult);
        }
        {
            beginTest ("Network returns false when asked to create a connexion with sourceIdentifier invalid.");
            Network network;
            auto sourceIdentifier = -10;
            auto destinationIdentifier = network.createNode ();
            expect (network.getNode (sourceIdentifier) == nullptr, "Bad initial conditions");
            auto creationResult = network.createConnexion (sourceIdentifier, destinationIdentifier);
            expect (!creationResult);
        }
        {
            beginTest ("Network returns false when asked to create a connexion with destinationIdentifier invalid.");
            Network network;
            auto sourceIdentifier = network.createNode ();
            auto destinationIdentifier = -10;
            expect (network.getNode (destinationIdentifier) == nullptr, "Bad initial conditions");
            auto creationResult = network.createConnexion (sourceIdentifier, destinationIdentifier);
            expect (!creationResult);
        }
        {
            beginTest ("Network returns true when asked to delete a connexion that exist.");
            Network network;
            auto nodeIdentifier1 = network.createNode ();
            auto nodeIdentifier2 = network.createNode ();
            auto creationResult = network.createConnexion (nodeIdentifier1, nodeIdentifier2);
            expect (creationResult, "Bad initial conditions");
            auto deletionResult = network.eraseConnexion (nodeIdentifier1, nodeIdentifier2);
            expect (deletionResult);
        }
        {
            beginTest ("Network returns false when asked to delete a connexion that does not exist.");
            Network network;
            auto nodeIdentifier1 = network.createNode ();
            auto nodeIdentifier2 = network.createNode ();
            auto deletionResult = network.eraseConnexion (nodeIdentifier1, nodeIdentifier2);
            expect (!deletionResult);
        }
        {
            beginTest ("Network can tell if a connexion exists or not.");
            Network network;
            auto nodeIdentifier1 = network.createNode ();
            auto nodeIdentifier2 = network.createNode ();
            auto nodeIdentifier3 = network.createNode ();
            network.createConnexion (nodeIdentifier1, nodeIdentifier2);
            expect (network.connexionExists (nodeIdentifier1, nodeIdentifier2));
            expect (!network.connexionExists (nodeIdentifier1, nodeIdentifier3));
            expect (!network.connexionExists (nodeIdentifier2, nodeIdentifier1));
            expect (!network.connexionExists (nodeIdentifier2, nodeIdentifier3));
            expect (!network.connexionExists (nodeIdentifier3, nodeIdentifier1));
            network.eraseConnexion (nodeIdentifier1, nodeIdentifier2);
            expect (!network.connexionExists (nodeIdentifier1, nodeIdentifier2));
        }
        {
            beginTest ("Network erases all connexions related to a node when it gets erased.");
            Network network;
            auto nodeIdentifier1 = network.createNode ();
            auto nodeIdentifier2 = network.createNode ();
            auto nodeIdentifier3 = network.createNode ();
            network.createConnexion (nodeIdentifier1, nodeIdentifier2);
            network.createConnexion (nodeIdentifier2, nodeIdentifier3);
            network.eraseNode (nodeIdentifier2);
            expect (!network.connexionExists (nodeIdentifier1, nodeIdentifier2));
            expect (!network.connexionExists (nodeIdentifier2, nodeIdentifier3));
        }
    }
} testTestNetwork;
}
