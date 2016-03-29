#ifndef CRDTSIMNETWORKCOMPONENT_H_INCLUDED
#define CRDTSIMNETWORKCOMPONENT_H_INCLUDED

#include "JuceHeader.h"
namespace crdtsim
{
class NetworkComponent : public juce::MultiDocumentPanel,
                         public juce::ValueTree::Listener
{
public:
    NetworkComponent ();
    bool tryToCloseDocument (juce::Component* component) override;
    void setNodesValueTree (juce::ValueTree newValueTree);
    void setConnexionsValueTree (juce::ValueTree newValueTree);
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) override;

private:
    juce::ValueTree nodesValueTree, connexionsValueTree;
};
} //namespace crdtsim
#endif // CRDTSIMNETWORKCOMPONENT_H_INCLUDED
