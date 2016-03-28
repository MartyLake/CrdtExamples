/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "crdtsimNetwork.h";

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
        setSize (800, 600);
        setFramesPerSecond (60);
        addAndMakeVisible (network.getComponent ());
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
        network.getComponent ()->setBounds (getLocalBounds ());
    }


private:
    crdtsim::Network network;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent () { return new MainContentComponent{}; }


#endif // MAINCOMPONENT_H_INCLUDED
