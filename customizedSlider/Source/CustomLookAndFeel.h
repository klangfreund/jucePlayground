/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 17 Sep 2014 2:32:45pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/** Custom Look And Feel subclass.

    From the JuceDemo:
    Simply override the methods you need to, anything else will be inherited from the base class.
    It's a good idea not to hard code your colours, use the findColour method along with appropriate
    ColourIds so you can set these on a per-component basis.
 */
struct CustomLookAndFeel    : public LookAndFeel_V3
{
    /** Draws the entire slider.
     */
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override;

    /** Draws the track of the slider.
     */
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const Slider::SliderStyle /*style*/, Slider& slider) override;
    
    /** Draws the thumb (the moving part) of the slider.
     */
    void drawLinearSliderThumb (Graphics& g, int x, int y, int width,
                                int height, float sliderPos,
                                float minSliderPos, float maxSliderPos,
                                const Slider::SliderStyle style,
                                Slider& slider) override;
};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
