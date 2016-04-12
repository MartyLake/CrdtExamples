/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "crdtsimNetworkComponent.h"
#include "crdtsimNetwork.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent : public AnimatedAppComponent
{
public:
    //==============================================================================
    MainContentComponent ()
    {
        //MODEL
        networkComponent.setNodesValueTree (network.getNodesValueTree ());
        networkComponent.setConnexionsValueTree (network.getConnexionsValueTree ());
        network.createNode ();
        //VIEW
        addAndMakeVisible (&networkComponent);
        setSize (800, 600);
        setFramesPerSecond (60);
    }

    ~MainContentComponent ()
    {
    }

    void update () override
    {
        // This function is called at the frequency specified by the setFramesPerSecond() call
        // in the constructor. You can use it to update counters, animate values, etc.
    }

    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (Colours::black);


        // You can add your drawing code here!
    }

    void resized () override
    {
        networkComponent.setBounds (getLocalBounds ());
    }


private:
    crdtsim::NetworkComponent networkComponent;
    crdtsim::Network network;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent () { return new MainContentComponent{}; }


#endif // MAINCOMPONENT_H_INCLUDED
