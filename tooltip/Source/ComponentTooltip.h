/*
  ==============================================================================

    ComponentTooltip.h
    Created: 23 Feb 2015 3:17:27pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef COMPONENTTOOLTIP_H_INCLUDED
#define COMPONENTTOOLTIP_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
    Displays help about the component below the mouse cursor.
 
    It's similar to the TooltipWindow, except:
    - Instead of plain text, a whole component will be displayed to help.
      Meaning it can also contain images.
    - The help bubble will always be at the same position, close to the
      TooltipWindow and not close to the mouse cursor.
*/
class ComponentTooltip    : public Component,
                            public Button::Listener
{
public:
    ComponentTooltip (Component* parentComponent = nullptr);
    ~ComponentTooltip();

    void paint (Graphics&);
    void resized();

private:
    virtual void buttonClicked (Button*);
    
    Component* parentComponent;
    TextButton enableTooltipButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentTooltip)
};


#endif  // COMPONENTTOOLTIP_H_INCLUDED
