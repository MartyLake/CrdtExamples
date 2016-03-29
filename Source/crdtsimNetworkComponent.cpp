#include "crdtsimNetworkComponent.h"

using namespace crdtsim;

NetworkComponent::NetworkComponent ()
{
    useFullscreenWhenOneDocument (false);
    setLayoutMode (LayoutMode::FloatingWindows);
}
bool NetworkComponent::tryToCloseDocument (juce::Component* component)
{
    //TODO
}
void NetworkComponent::setNodesValueTree (juce::ValueTree newValueTree)
{
    nodesValueTree = newValueTree;
    nodesValueTree.addListener (this);
}
void NetworkComponent::setConnexionsValueTree (juce::ValueTree newValueTree)
{
    connexionsValueTree = newValueTree;
    connexionsValueTree.addListener (this);
}
void NetworkComponent::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    //TODO
}
void NetworkComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    if (parentTree == nodesValueTree)
    {
        auto identifier = childWhichHasBeenAdded.getType ();
        auto newNote = new juce::TextButton{};
        newNote->setButtonText (identifier.toString ());
        addDocument (newNote, Colours::lightblue.withAlpha (0.6f), true);
    }
    else if (parentTree == connexionsValueTree)
    {
        //TODO
    }
    else
    {
        jassertfalse;
    }
}
void NetworkComponent::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int /*indexFromWhichChildWasRemoved*/)
{
    if (parentTree == nodesValueTree)
    {
        //TODO
    }
    else if (parentTree == connexionsValueTree)
    {
        //TODO
    }
    else
    {
        jassertfalse;
    }
}
void NetworkComponent::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    //TODO
}
void NetworkComponent::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{
    //TODO
}
