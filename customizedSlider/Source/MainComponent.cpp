/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
    : labelLookAndFeel (String::empty, "using LookAndFeel"),
      sliderUsingLookAndFeel (Slider::SliderStyle::LinearVertical, Slider::TextBoxBelow),
      labelCustom (String::empty, "using inheritance"),
      customSlider (Slider::SliderStyle::LinearVertical, Slider::TextBoxBelow)

{
    setSize (300, 400);
    
    labelLookAndFeel.setJustificationType(Justification::horizontallyCentred);
    labelCustom.setJustificationType(Justification::horizontallyCentred);
    
    addAndMakeVisible (&labelLookAndFeel);
    addAndMakeVisible (&sliderUsingLookAndFeel);
    addAndMakeVisible (&labelCustom);
    addAndMakeVisible (&customSlider);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void MainContentComponent::resized()
{
    const int border = 10;
    const int labelHeight = 20;
    labelLookAndFeel.setBounds(border, border, getWidth()/2 - border, labelHeight);
    sliderUsingLookAndFeel.setBounds(border, labelLookAndFeel.getBottom(), labelLookAndFeel.getWidth(), getHeight() - labelLookAndFeel.getBottom() - border);
    
    labelCustom.setBounds(getWidth()/2, border, getWidth()/2 - border, labelHeight);
    customSlider.setBounds(getWidth()/2, labelCustom.getBottom(), labelCustom.getWidth(), getHeight() - labelCustom.getBottom() - border);
}
