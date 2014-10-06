/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
    // : slider (Slider::SliderStyle::LinearVertical, Slider::TextBoxBelow)
{
    setSize (150, 600);
    
    // lookAndFeelSlider
    // -----------------
    // setLookAndFeel is a member function of Component.
    // Each Component can be assigned with its own LookAndFeel.
    slider.setLookAndFeel (&klangfreundLookAndFeel);
    slider.setRange (-15.0, 15.0, 0.01);
    
    addAndMakeVisible (&slider);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (JUCE_LIVE_CONSTANT (Colours::lightgrey));
    
    slider.setColour(Slider::thumbColourId, JUCE_LIVE_CONSTANT (Colours::white));
}

void MainContentComponent::resized()
{
    const int border = 10;
    slider.setBounds(border, border, getWidth() - 2 * border, getHeight() - 2 * border);
}
