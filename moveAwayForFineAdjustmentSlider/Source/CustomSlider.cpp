/*
  ==============================================================================

    CustomSlider.cpp
    Created: 1 Oct 2014 6:48:58pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomSlider.h"

//==============================================================================
CustomSlider::CustomSlider()
    : Slider (Slider::SliderStyle::LinearVertical, Slider::TextBoxBelow)
{
}


CustomSlider::~CustomSlider()
{
}

void CustomSlider::resized()
{
    Slider::resized();
    
    
    // Code copied from Slider::resized (const Rectangle<int>& localBounds, LookAndFeel& lf)
    
    // TextBox height
    const int tbh = jmax (0, jmin (getTextBoxHeight(), getHeight()));
    
    // if (textBoxPos == TextBoxBelow)
    sliderRect.setBounds (0, 0, getWidth(), getHeight() - tbh);
    
    const int indent = getLookAndFeel().getSliderThumbRadius (*this);
    
    // if (isVertical())
    sliderRegionStart = sliderRect.getY() + indent;
    sliderRegionSize = jmax (1, sliderRect.getHeight() - indent * 2);
    
    sliderRect.setBounds (sliderRect.getX(), sliderRegionStart,
                          sliderRect.getWidth(), sliderRegionSize);
}

void CustomSlider::setChangeNotificationOnlyOnRelease (bool onlyNotifyOnRelease)
{
    Slider::setChangeNotificationOnlyOnRelease (onlyNotifyOnRelease);
    
    sendChangeOnlyOnRelease = onlyNotifyOnRelease;
}

void CustomSlider::mouseDown (const MouseEvent& e)
{
    Slider::mouseDown(e);
    
    mouseDragStartPos = e.position;
    
    if (isEnabled())
    {
        if (getMaximum() > getMinimum())
        {
            valueOnMouseDown = getValue();
        }
    }
}

void CustomSlider::mouseDrag (const MouseEvent& e)
{
    DragMode dragMode = notDragging;
    
    const int indent = getLookAndFeel().getSliderThumbRadius(*this);
    int sliderRegionSize = jmax (1, getHeight() - indent * 2);
        
    if (isAbsoluteDragMode (e.mods) || (getMaximum() - getMinimum()) / sliderRegionSize < getInterval())
    {
        dragMode = absoluteDrag;
        handleAbsoluteDrag (e); // This sets the valueWhenLastDragged
        
        valueWhenLastDragged = jlimit (getMinimum(), getMaximum(), valueWhenLastDragged);
        
        setValue (snapValue (valueWhenLastDragged, dragMode),
                  sendChangeOnlyOnRelease ? dontSendNotification : sendNotificationSync);
            // This calls pimpl->setValue()
    }
    else
    {
        Slider::mouseDrag(e);
    }
}

bool CustomSlider::isAbsoluteDragMode (ModifierKeys mods) const
{
    return getVelocityBasedMode() == (getVelocityModeIsSwappable()
                               && mods.testFlags (ModifierKeys::ctrlAltCommandModifiers));
}

void CustomSlider::handleAbsoluteDrag (const MouseEvent& e)
{
    // This is copied from the Slider::Pimpl::handleAbsoluteDrag().
    
    const float mousePos = e.position.y;
    // The newPos is the current mouse position measured from the top of the
    // slider. newPos /in [0.0, 1.0]
    double newPos = (mousePos - sliderRegionStart) / (double) sliderRegionSize;
    
    if (!getSliderSnapsToMousePosition())
    {
        const float mouseDiff = mouseDragStartPos.y - e.position.y;
        
        newPos = valueToProportionOfLength (valueOnMouseDown)
        + mouseDiff * (1.0 / getMouseDragSensitivity());
    }
    else
    {
        if (isVertical())
            // Now, newPos is measured from the bottom of the slider.
            newPos = 1.0 - newPos;
    }
    
    valueWhenLastDragged = proportionOfLengthToValue (jlimit (0.0, 1.0, newPos));
}