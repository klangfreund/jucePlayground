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
            valueWhenLastDragged = getValue();
            lastMousePos = e.position.y;
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
        // handleAbsoluteDrag (e);
        handleDragWithFineAdjustmentFurtherAway (e); // This sets the valueWhenLastDragged
        
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

// This is copied from the Slider::Pimpl::handleAbsoluteDrag().
void CustomSlider::handleAbsoluteDrag (const MouseEvent& e)
{
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

void CustomSlider::handleDragWithFineAdjustmentFurtherAway (const MouseEvent& e)
{
    // y position of the mouse
    // -----------------------
    const float mousePos = e.position.y;
    const float mousePosDifference = mousePos - lastMousePos;
    
    // A mousePosDifference > 0 (measured from the top to the bottom) means that
    // the value (which is measured from the bottom to the top) needs to be decreased.
    // That's the reason for the negation.
    // The max absolute value of posDifference is 1.
    double posDifference = - mousePosDifference / (double) sliderRegionSize;
    
    // x position of the mouse
    // -----------------------
    const float horizontalMousePosDifference =  std::abs (e.position.x - mouseDragStartPos.x);
    const float horizontalOffset = 20.0f;
    // If the current mouse position e.position.x is in the interval
    // [mouseDragStartPos.x - horizontalOffset, mouseDragStartPos.x + horizontalOffset]
    // there won't be a decrease of the slider movement.
    const float minimizingFactor = horizontalMousePosDifference < horizontalOffset ?
        1.0f
        : 1.0f / (0.1f * (horizontalMousePosDifference - horizontalOffset) + 1.0f);
    
    // Set valueWhenLastDragged
    // ------------------------
    valueWhenLastDragged = jlimit(getMinimum(), getMaximum(), valueWhenLastDragged + (getMaximum() - getMinimum()) * (posDifference * minimizingFactor));
    
    lastMousePos = mousePos;
}