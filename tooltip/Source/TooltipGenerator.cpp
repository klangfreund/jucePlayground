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
    Label* l = new Label();

    // Colours
    l->setColour(Label::backgroundColourId, Colours::transparentBlack);
    l->setColour(Label::textColourId, Colours::white);
    
    // Text
    l->setText (text, NotificationType::dontSendNotification);
    l->setMinimumHorizontalScale (1.0f);
    l->setJustificationType (Justification::verticallyCentred);
    l->setBorderSize (BorderSize <int> (5, 5, 5, 5));
    
    // Figure out the size of the component
    Font f = l->getFont();
    
    StringArray lines;
    lines.addLines (text); // text is split wherever a \r or \n occur.
    
    int width = 0;
    for (int i = 0; i < lines.size(); ++i) 
    {
        width = jmax(width, f.getStringWidth (lines[i]));
    }
    
    const int nrOfLines = lines.size();
    const int height = nrOfLines * f.getHeight();
    l->setSize (width + 10 + l->getBorderSize().getLeftAndRight(), 
                height + l->getBorderSize().getTopAndBottom());
    
    labels.add (l);
    
    return l;
}