/*
  ==============================================================================

    TooltipGenerator.cpp
    Created: 23 Feb 2015 5:59:56pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TooltipGenerator.h"

//==============================================================================
TooltipGenerator::TooltipGenerator()
{
}

TooltipGenerator::~TooltipGenerator()
{
}

Component* TooltipGenerator::generateTextOnlyComponent (String text)
{
    Label* t = new Label();
    t->setSize (180, 100);
    t->setColour(Label::backgroundColourId, Colours::transparentBlack);
    t->setColour(Label::textColourId, Colours::white);
    t->setText (text, NotificationType::dontSendNotification);
    t->setJustificationType (Justification::centred);
    t->setMinimumHorizontalScale (1.0f);
    t->setBorderSize (BorderSize <int> (5, 5, 5, 5));
    //t->setScrollbarsShown (false);
    //t->setSize (t->getTextWidth(), t->getTextHeight() + 10);
    
    labels.add (t);
    
    return t;
}
