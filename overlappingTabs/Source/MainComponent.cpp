/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (300, 150);
    
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeelV3);
    
    addAndMakeVisible(&secondComponent);
    
    // Workaround 1:
    // Move setSize() below the LookAndFeel change.
    
    // // Workaround 2
    // // (Not quite safe)
    // secondComponent.setLookAndFeel(&lookAndFeelV3);
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
    secondComponent.setBounds(getBounds());
}
