/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
    : lookAndFeelLabel (String::empty, "using LookAndFeel"),
      lookAndFeelSlider (Slider::SliderStyle::LinearVertical, Slider::TextBoxBelow),
      customLabel (String::empty, "using inheritance"),
      customSlider (Slider::SliderStyle::LinearVertical, Slider::TextBoxBelow)

{
    setSize (300, 600);
    
    // Labels
    // ------
    lookAndFeelLabel.setJustificationType(Justification::horizontallyCentred);
    customLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible (&lookAndFeelLabel);
    addAndMakeVisible (&customLabel);
    
    // lookAndFeelSlider
    // -----------------
    // setLookAndFeel is a member function of Component.
    // Each Component can be assigned with its own LookAndFeel.
    lookAndFeelSlider.setLookAndFeel (&customLookAndFeel);
    
    lookAndFeelSlider.setColour(Slider::thumbColourId, Colours::blue);
    addAndMakeVisible (&lookAndFeelSlider);

    // customSlider
    // ------------
    addAndMakeVisible (&customSlider);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (JUCE_LIVE_CONSTANT (Colours::lightgrey));
}

void MainContentComponent::resized()
{
    const int border = 10;
    const int labelHeight = 20;
    lookAndFeelLabel.setBounds(border, border, getWidth()/2 - border, labelHeight);
    lookAndFeelSlider.setBounds(border, lookAndFeelLabel.getBottom(), lookAndFeelLabel.getWidth(), getHeight() - lookAndFeelLabel.getBottom() - border);
    
    customLabel.setBounds(getWidth()/2, border, getWidth()/2 - border, labelHeight);
    customSlider.setBounds(getWidth()/2, customLabel.getBottom(), customLabel.getWidth(), getHeight() - customLabel.getBottom() - border);
}
