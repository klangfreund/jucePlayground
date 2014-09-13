/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
:
backgroundColourSelector {ColourSelector::showColourspace}
{
    setSize (500, 400);
    
    addAndMakeVisible(&backgroundColourSelector);
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
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    backgroundColourSelector.setBounds(0, 0, getWidth(), 200);
}
