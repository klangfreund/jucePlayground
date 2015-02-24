/*
  ==============================================================================

    TooltipGenerator.h
    Created: 23 Feb 2015 5:59:55pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef TOOLTIPGENERATOR_H_INCLUDED
#define TOOLTIPGENERATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TooltipGenerator
{
public:
    TooltipGenerator();
    ~TooltipGenerator();

    static Component* generateTextOnlyComponent (String text);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TooltipGenerator)
};


#endif  // TOOLTIPGENERATOR_H_INCLUDED
