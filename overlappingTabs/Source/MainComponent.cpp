/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeelV3);
    // // Is this the most elegant solution?:
    // secondComponent.setLookAndFeel(&lookAndFeelV3);
    
    addAndMakeVisible(&secondComponent);
    
    setSize (300, 150);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffeeddff));
}

void MainContentComponent::resized()
{
    secondComponent.setTopLeftPosition(0, 0);
}
