/*
  ==============================================================================

    SecondComponent.h
    Created: 31 Oct 2014 3:44:35pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef SECONDCOMPONENT_H_INCLUDED
#define SECONDCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SecondComponent    : public Component
{
public:
    SecondComponent();
    ~SecondComponent();

    void paint (Graphics&);
    void resized();

private:
    // ========================================================================
    class MyTabbedComponent : public TabbedComponent
    {
    public:
        MyTabbedComponent();
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyTabbedComponent)
    };
    
    MyTabbedComponent myTabbedComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SecondComponent)
};


#endif  // SECONDCOMPONENT_H_INCLUDED
