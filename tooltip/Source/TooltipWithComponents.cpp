/*
  ==============================================================================

    TooltipWithComponents.cpp
    Created: 23 Feb 2015 3:17:27pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TooltipWithComponents.h"

//==============================================================================
TooltipWithComponents::TooltipWithComponents (Component* parentComponent_)
  : parentComponent (parentComponent_),
    enableTooltipButton ("Klangfreund tooltips")
{
    enableTooltipButton.setClickingTogglesState (true);
    enableTooltipButton.addListener (this);
    enableTooltipButton.setToggleState (true, NotificationType::sendNotification);
    addAndMakeVisible (enableTooltipButton);
}

TooltipWithComponents::~TooltipWithComponents()
{
    hideTip();
    
//    HashMap<Component*, Component*>::Iterator i (tooltips);
//    
//    while (i.next())
//    {
//        delete i.getValue();
//    }
}

void TooltipWithComponents::paint (Graphics& g)
{
}

void TooltipWithComponents::resized()
{
    enableTooltipButton.setBounds (0, 0, getWidth(), getHeight());
}

void TooltipWithComponents::addTooltip (Component* const componentToDescribe, Component* const tip)
{
    tooltips.set (componentToDescribe, tip);
}

void TooltipWithComponents::buttonClicked (Button* button)
{
    if (button == & enableTooltipButton)
    {
        if (enableTooltipButton.getToggleState())
        {
            if (Desktop::getInstance().getMainMouseSource().canHover())
                startTimer (123);
        }
        else
        {
            stopTimer();
            hideTip();
        }
    }
}

void TooltipWithComponents::timerCallback()
{
    // Big chunks of this code are taken from TooltipWindow::timerCallback().

    const unsigned int now = Time::getApproximateMillisecondCounter();
    
    Desktop& desktop = Desktop::getInstance();
    const MouseInputSource mouseSource (desktop.getMainMouseSource());
    Component* newComp = mouseSource.isMouse() ? mouseSource.getComponentUnderMouse() : nullptr;
    
    
    // This avoids an infinite on / off cycle when the mouse is over the
    // tooltip and behind the tooltip is a Component with a tooltip.
    if (tipBox.get() != nullptr)
    {
        if (newComp == tipBox)
            newComp = lastComponentUnderMouse;
        else
        {
            for (int i = 0; i < tipBox->getNumChildComponents(); ++i) 
            {
                if (newComp == tipBox->getChildComponent (i))
                    newComp = lastComponentUnderMouse;
            }
        }
    }

    // Find the tip for the component under the mouse cursor.
    Component* newTip = nullptr;
    if (newComp != nullptr)
        newTip = tooltips [newComp];
    
    // If the component could't be found, the parent might have been registered.
    if (newTip == nullptr && newComp != nullptr)
    {
        newTip = tooltips [newComp->getParentComponent()];
    }

    const bool tipChanged = (newTip != lastTipUnderMouse || newComp != lastComponentUnderMouse);
    lastComponentUnderMouse = newComp;
    lastTipUnderMouse = newTip;
    
    const int mouseClicks = desktop.getMouseButtonClickCounter();
    const int wheelMoves = desktop.getMouseWheelMoveCounter();
    const bool mouseWasClicked = (mouseClicks > lastMouseClicks || wheelMoves > lastMouseWheelMoves);
    lastMouseClicks = mouseClicks;
    lastMouseWheelMoves = wheelMoves;
    
    const Point<float> mousePos (mouseSource.getScreenPosition());
    const bool mouseMovedQuickly = mousePos.getDistanceFrom (lastMousePos) > 12;
    lastMousePos = mousePos;


    if (tipChanged || mouseWasClicked || mouseMovedQuickly)
        lastCompChangeTime = now;
    
    if (tipIsVisible() || now < lastHideTime + 500) 
    {
        // if a tip is currently visible (or has just disappeared), update to a 
        // new one immediately if needed..
        if (newComp == nullptr || mouseWasClicked || newTip == nullptr)
        {
            if (tipIsVisible())
            {
                lastHideTime = now;
                hideTip();
            }
        }
        else if (tipChanged)
        {
            displayTip (newTip);
        }
    }
    else
    {
        // Ff there isn't currently a tip, but one is needed, only let it
        // appear after a timeout..
        if (newTip != nullptr
            && now > lastCompChangeTime + (unsigned int) millisecondsBeforeTipAppears)
        {
            displayTip (newTip);
        }
    }
}

void TooltipWithComponents::displayTip (Component* tip)
{
    if (tip != nullptr)
    {
        tipBox = new CallOutBox (*tip, getBounds(), parentComponent);
        currentTip = tip;
    }
}

void TooltipWithComponents::hideTip()
{
    tipBox = nullptr;
    currentTip = nullptr;
}

bool TooltipWithComponents::tipIsVisible()
{
    return tipBox.get() != nullptr;
}
