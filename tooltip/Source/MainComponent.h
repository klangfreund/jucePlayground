/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ComponentTooltip.h"
#include "TooltipGenerator.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
                               public Button::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();

private:
    //==============================================================================
    virtual void buttonClicked (Button* button);
    
    TextButton dummyButton;
    Slider dummySlider;
    
    // Klangfreund Tooltip
    ComponentTooltip componentTooltip;
    TooltipGenerator tooltipGenerator;
    
    // JUCE Tooltip
    TextButton juceTooltipButton;
    ScopedPointer<TooltipWindow> tooltipWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
