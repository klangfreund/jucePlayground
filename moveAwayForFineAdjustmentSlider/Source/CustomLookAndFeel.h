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
class CustomLookAndFeel    : public LookAndFeel_V3
{
public:
    /** For a vertical slider, it returns height/2 of the thumb of the slider plus
        a minimal border (spaceBetweenThumbAndComponentBorder).
     
        The slider class needs this to know where the minimal and maximal positions
        of the thumb are, such it won't be clipped.
     */
    int getSliderThumbRadius (Slider& slider) override;
    
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
private:
    static constexpr float spaceBetweenThumbAndComponentBorder {4.0f};
    static constexpr float maxThumbWidthVertical {60.0f};
    static constexpr float heightToWidthRatioVertical {0.45f};
};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
