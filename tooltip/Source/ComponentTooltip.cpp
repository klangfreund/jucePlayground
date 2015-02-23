/*
  ==============================================================================

    ComponentTooltip.cpp
    Created: 23 Feb 2015 3:17:27pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ComponentTooltip.h"

//==============================================================================
ComponentTooltip::ComponentTooltip (Component* parentComponent_)
  : parentComponent (parentComponent_),
    enableTooltipButton ("help")
{
    enableTooltipButton.setClickingTogglesState (true);
    enableTooltipButton.addListener (this);
    // enableTooltipButton.setToggleState (false, NotificationType::sendNotification);
    addAndMakeVisible (enableTooltipButton);
}

ComponentTooltip::~ComponentTooltip()
{
}

void ComponentTooltip::paint (Graphics& g)
{
}

void ComponentTooltip::resized()
{
    enableTooltipButton.setBounds (0, 0, getWidth(), getHeight());
}

void ComponentTooltip::buttonClicked (Button* button)
{
    if (button == & enableTooltipButton)
    {
        if (enableTooltipButton.getToggleState())
        {
            Component* content = new Component();
            content->setSize (300, 100);
            CallOutBox& myBox = CallOutBox::launchAsynchronously (content, getBounds(), parentComponent);
        }
    }
}