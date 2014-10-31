/*
  ==============================================================================

    SecondComponent.cpp
    Created: 31 Oct 2014 3:44:35pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SecondComponent.h"

//==============================================================================
SecondComponent::SecondComponent()
{
    addAndMakeVisible(&myTabbedComponent);

}

SecondComponent::~SecondComponent()
{
}

void SecondComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background
}

void SecondComponent::resized()
{
    myTabbedComponent.setBounds(getBounds());
}

SecondComponent::MyTabbedComponent::MyTabbedComponent()
: TabbedComponent (TabbedButtonBar::TabsAtTop)
{
    addTab ("Juce", Colours::red.withAlpha (0.5f), new Component(), true);
    addTab ("is", Colours::green.withAlpha (0.5f), new Component(), true);
    addTab ("lovely", Colours::blue.withAlpha (0.5f), new Component(), true);
}

