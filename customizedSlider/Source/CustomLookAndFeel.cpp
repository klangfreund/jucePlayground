/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 17 Sep 2014 2:32:45pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "CustomLookAndFeel.h"


void CustomLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                          float sliderPos, float minSliderPos, float maxSliderPos,
                                          const Slider::SliderStyle style, Slider& slider)
{
    // Fill the whole background of the slider
    g.fillAll (slider.findColour (Slider::backgroundColourId));

    if (style != Slider::LinearBar && style != Slider::LinearBarVertical)

    {
        drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}

void CustomLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                                    float /*sliderPos*/,
                                                    float /*minSliderPos*/,
                                                    float /*maxSliderPos*/,
                                                    const Slider::SliderStyle /*style*/, Slider& slider)
{
    const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
    
    const Colour trackColour (slider.findColour (Slider::trackColourId));
    const Colour gradCol1 (trackColour.overlaidWith (Colours::black.withAlpha (slider.isEnabled() ? 0.5f : 0.25f)));
    const Colour gradCol2 (trackColour.overlaidWith (Colour (0x14000000)));
    Path indent;
    
    if (slider.isHorizontal())
    {
        const float iy = y + height * 0.5f - sliderRadius * 0.5f;
        const float ih = sliderRadius;
        
        g.setGradientFill (ColourGradient (gradCol1, 0.0f, iy,
                                           gradCol2, 0.0f, iy + ih, false));
        
        indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy,
                                    width + sliderRadius, ih,
                                    5.0f);
    }
    else
    {
        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
        const float iw = sliderRadius;
        
        g.setGradientFill (ColourGradient (gradCol1, ix, 0.0f,
                                           gradCol2, ix + iw, 0.0f, false));
        
        indent.addRoundedRectangle (ix, y - sliderRadius * 0.5f,
                                    iw, height + sliderRadius,
                                    5.0f);
    }
    
    g.fillPath (indent);
    
    g.setColour (Colour (0x4c000000));
    g.strokePath (indent, PathStrokeType (0.5f));
}

void CustomLookAndFeel::drawLinearSliderThumb (Graphics& g, int x, int y, int width,
                                               int height, float sliderPos,
                                               float minSliderPos, float maxSliderPos,
                                               const Slider::SliderStyle style,
                                               Slider& slider)
{
    const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
    
    bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
    Colour knobColour (slider.findColour (Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                       .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));
    
    if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
    {
        float kx, ky;
        
        if (style == Slider::LinearVertical)
        {
            kx = x + width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = y + height * 0.5f;
        }
        
        const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;
        
        // Draw the actual knob
        float xThumb = kx - sliderRadius;
        float yThumb = ky - sliderRadius;
        const Rectangle<float> a (xThumb, yThumb, sliderRadius * 2.0f, sliderRadius * 2.0f);
        const float halfThickness = outlineThickness * 0.5f;
        
        Path p;
        p.addEllipse (xThumb + halfThickness, yThumb + halfThickness, sliderRadius * 2.0f - outlineThickness, sliderRadius * 2.0f - outlineThickness);
        
        const DropShadow ds (Colours::black, 1, Point<int> (0, 0));
        ds.drawForPath (g, p);
        
        g.setColour (knobColour);
        g.fillPath (p);
        
        g.setColour (knobColour.brighter());
        g.strokePath (p, PathStrokeType (outlineThickness));
    }
    else
    {
        // Just call the base class for the demo
        LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}
