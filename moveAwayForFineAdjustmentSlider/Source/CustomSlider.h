/*
  ==============================================================================

    CustomSlider.h
    Created: 1 Oct 2014 6:48:58pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef CUSTOMSLIDER_H_INCLUDED
#define CUSTOMSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This is a linear vertical slider.
 
    Nothing more. It was intended to create a inherited slider which looks
    identical to the LookAndFeel one.
    But it's quite cumbersome... -> Go the look and feel path for a custom slider
*/
class CustomSlider    : public Slider
{
public:
    CustomSlider();
    ~CustomSlider();

    void resized() override;
    
    void setChangeNotificationOnlyOnRelease (bool onlyNotifyOnRelease);

private:
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent&) override;
    bool isAbsoluteDragMode (ModifierKeys mods) const;
    void handleAbsoluteDrag (const MouseEvent& e);

    bool sendChangeOnlyOnRelease {false};
    double valueOnMouseDown {0.0};
    double valueWhenLastDragged {0.0};
    Point<float> mouseDragStartPos;
    int sliderRegionStart {0};
    int sliderRegionSize {0};
    Rectangle<int> sliderRect;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};


#endif  // CUSTOMSLIDER_H_INCLUDED
