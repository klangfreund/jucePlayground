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
#include <map>

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
                            private Button::Listener,
                            private Timer
{
public:
    ComponentTooltip (Component* parentComponent = nullptr);
    ~ComponentTooltip();

    void paint (Graphics&);
    void resized();
    
    /**
     @param description It takes the ownership of this component.
     */
    void addTooltip (Component* const componentToDescribe, Component* const tip);

private:
    void buttonClicked (Button*);
    void timerCallback();
    
    void displayTip (Component* tip);
    void hideTip();
    bool tipIsVisible();
    
    Component* parentComponent;
    TextButton enableTooltipButton;
    ScopedPointer<CallOutBox> tipBox;
    
    //std::map <Component*, Component*> tooltips; // {{nullptr, nullptr}};
    HashMap <Component*, Component*> tooltips;
        // HashMap does not work with ScopedPointer<Component> as second argument.
    
    int millisecondsBeforeTipAppears {700};
    
    // Used in the timerCallback()
    Component* lastComponentUnderMouse {nullptr};
    Component* lastTipUnderMouse {nullptr};
    Component* currentTip {nullptr};
    int lastMouseClicks {0};
    int lastMouseWheelMoves {0};
    Point<float> lastMousePos {0.0, 0.0};
    unsigned int lastCompChangeTime;
    unsigned int lastHideTime;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentTooltip)
};


#endif  // COMPONENTTOOLTIP_H_INCLUDED
