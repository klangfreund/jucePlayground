/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
  : dummyButton ("Dummy"),
    dummySlider (Slider::LinearHorizontal, Slider::TextBoxLeft),
    tooltip (this),
    juceTooltipButton ("JUCE tooltips")
{
    dummyButton.setTooltip ("A button that does...\r"
                            "absolutely nothing.");
    tooltip.addTooltip (&dummyButton, tooltipGenerator.generateTextOnlyComponent (dummyButton.getTooltip()));
    addAndMakeVisible (dummyButton);
    
    dummySlider.setRange (0.0, 10.0);
    dummySlider.setTooltip ("A slider with no influence at all.");
    tooltip.addTooltip (&dummySlider, tooltipGenerator.generateTextOnlyComponent (dummySlider.getTooltip()));
    addAndMakeVisible (dummySlider);
    
    tooltip.addTooltip (&tooltip, 
                                 tooltipGenerator.generateTextOnlyComponent (
                                    "Click to activate\r"
                                    "or deactivate\r"
                                    "this help bubble."));
    addAndMakeVisible (tooltip);
    
    juceTooltipButton.setClickingTogglesState (true);
    juceTooltipButton.setTooltip ("Enables or disables the JUCE tooltip window.");
    tooltip.addTooltip (&juceTooltipButton, tooltipGenerator.generateTextOnlyComponent (juceTooltipButton.getTooltip()));
    juceTooltipButton.addListener (this);
    juceTooltipButton.setToggleState (false, NotificationType::sendNotification);
    addAndMakeVisible (juceTooltipButton);
    
    setSize (400, 220);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);

//    g.setFont (Font (16.0f));
//    g.setColour (Colours::black);
//    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    dummyButton.setTopLeftPosition (10, 10);
    dummyButton.setSize (80, 20);
    //dummyButton.changeWidthToFitText();
    
    dummySlider.setBounds (10, dummyButton.getBottom() + 10, getWidth() - 20, 40);
    
    tooltip.setBounds(10, getHeight() - 30, 120, 20);
    
    juceTooltipButton.setBounds(tooltip.getRight() + 10, getHeight() - 30, 80, 20);
    juceTooltipButton.changeWidthToFitText();
}

void MainContentComponent::buttonClicked (Button* button)
{
    if (button == &juceTooltipButton)
    {
        if (button->getToggleState())
        {
            // Enable the tooltips
            tooltipWindow = new TooltipWindow (this, 700);
        }
        else
        {
            // Disable the tooltips
            tooltipWindow = nullptr;
        }
    }
}
