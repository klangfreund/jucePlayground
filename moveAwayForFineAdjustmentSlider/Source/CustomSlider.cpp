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
        handleAbsoluteDrag (e); // -> valueWhenLastDragged
        
        valueWhenLastDragged = jlimit (getMinimum(), getMaximum(), valueWhenLastDragged);
        
        // This would be set by Slider::setChangeNotificationOnlyOnRelease
        bool sendChangeOnlyOnRelease = false;
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
    const SliderStyle style = getSliderStyle();
    
    const float mousePos = (isHorizontal() || style == RotaryHorizontalDrag) ? e.position.x : e.position.y;
    double newPos = (mousePos - sliderRegionStart) / (double) sliderRegionSize;
    
    if (style == RotaryHorizontalDrag
        || style == RotaryVerticalDrag
        || style == IncDecButtons
        || ((style == LinearHorizontal || style == LinearVertical || style == LinearBar || style == LinearBarVertical)
            && ! getSliderSnapsToMousePosition()))
    {
        const float mouseDiff = (style == RotaryHorizontalDrag
                                 || style == LinearHorizontal
                                 || style == LinearBar)
        ? e.position.x - mouseDragStartPos.x
        : mouseDragStartPos.y - e.position.y;
        
        newPos = valueToProportionOfLength (valueOnMouseDown)
        + mouseDiff * (1.0 / getMouseDragSensitivity());
    }
    else
    {
        if (isVertical())
            newPos = 1.0 - newPos;
    }
    
    valueWhenLastDragged = proportionOfLengthToValue (jlimit (0.0, 1.0, newPos));
}

void CustomSlider::resized()
{
    Slider::resized();

     
    LookAndFeel& lf = getLookAndFeel();
    
    // Code copied from Slider::resized (const Rectangle<int>& localBounds, LookAndFeel& lf)
    
    // TextBox height
     const int tbh = jmax (0, jmin (getTextBoxHeight(), getHeight()));
     
     // if (textBoxPos == TextBoxBelow)
     sliderRect.setBounds (0, 0, getWidth(), getHeight() - tbh);
     
     const int indent = lf.getSliderThumbRadius (*this);
     
     // if (isVertical())
     sliderRegionStart = sliderRect.getY() + indent;
     sliderRegionSize = jmax (1, sliderRect.getHeight() - indent * 2);
     
     sliderRect.setBounds (sliderRect.getX(), sliderRegionStart,
     sliderRect.getWidth(), sliderRegionSize);
}