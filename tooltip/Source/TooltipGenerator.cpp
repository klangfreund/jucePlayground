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
    TextEditor* t = new TextEditor();
    t->setSize (200, 100);
    t->setColour(TextEditor::backgroundColourId, Colours::transparentBlack);
    t->setColour(TextEditor::textColourId, Colours::white);
    t->setReadOnly (true);
    t->setText (text);
    
    return t;
}
