#ifndef CRDTSIMNETWORKCOMPONENT_H_INCLUDED
#define CRDTSIMNETWORKCOMPONENT_H_INCLUDED

#include "JuceHeader.h"
namespace crdtsim
{
class NetworkComponent : public juce::MultiDocumentPanel
{
public:
    bool tryToCloseDocument (juce::Component* component) override;
};
} //namespace crdtsim
#endif // CRDTSIMNETWORKCOMPONENT_H_INCLUDED
