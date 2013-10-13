/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include <iostream>
//[/Headers]

#include "MainContentComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
using namespace std;
//[/MiscUserDefs]

//==============================================================================
MainContentComponent::MainContentComponent ()
:
    mainValueTreeId ("mainValueTreeId"),
    mainValueTree (mainValueTreeId),
    slider1Id ("slider1"),
    slider2Id ("slider2"),
    slider3Id ("slider3")
{
    addAndMakeVisible (undoButton = new TextButton ("undo button"));
    undoButton->setButtonText ("undo");
    undoButton->addListener (this);

    addAndMakeVisible (redoButton = new TextButton ("redo button"));
    redoButton->setButtonText ("redo");
    redoButton->addListener (this);

    addAndMakeVisible (slider1 = new Slider ("slider 1"));
    slider1->setRange (0, 10, 0);
    slider1->setSliderStyle (Slider::LinearHorizontal);
    slider1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider1->addListener (this);

    addAndMakeVisible (slider2 = new Slider ("slider 2"));
    slider2->setRange (0, 10, 0);
    slider2->setSliderStyle (Slider::LinearHorizontal);
    slider2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider2->addListener (this);

    addAndMakeVisible (slider3 = new Slider ("slider 3"));
    slider3->setRange (0, 10, 0);
    slider3->setSliderStyle (Slider::LinearHorizontal);
    slider3->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider3->addListener (this);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (450, 150);

    //[Constructor] You can add your own custom stuff here..
    
    // Create the value tree properties
    double initValue = 5;
    mainValueTree.setProperty (slider1Id, initValue, &undoManager);
    mainValueTree.setProperty (slider2Id, initValue, &undoManager);
    mainValueTree.setProperty (slider3Id, initValue, &undoManager);
    
    slider1->getValueObject().referTo (mainValueTree.getPropertyAsValue (slider1Id, &undoManager));
    slider2->getValueObject().referTo (mainValueTree.getPropertyAsValue (slider2Id, &undoManager));
    slider3->getValueObject().referTo (mainValueTree.getPropertyAsValue (slider3Id, &undoManager));
    
    undoManager.clearUndoHistory();
    //[/Constructor]
}

MainContentComponent::~MainContentComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    undoButton = nullptr;
    redoButton = nullptr;
    slider1 = nullptr;
    slider2 = nullptr;
    slider3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainContentComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffdddddd));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainContentComponent::resized()
{
    undoButton->setBounds (16, 16, 200, 24);
    redoButton->setBounds (232, 16, 200, 24);
    slider1->setBounds (24, 64, 408, 24);
    slider2->setBounds (24, 88, 408, 24);
    slider3->setBounds (24, 112, 408, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainContentComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == undoButton)
    {
        //[UserButtonCode_undoButton] -- add your button handler code here..
        undoManager.undo();
        //[/UserButtonCode_undoButton]
    }
    else if (buttonThatWasClicked == redoButton)
    {
        //[UserButtonCode_redoButton] -- add your button handler code here..
        undoManager.redo();
        //[/UserButtonCode_redoButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainContentComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    undoManager.beginNewTransaction();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider1)
    {
        //[UserSliderCode_slider1] -- add your slider handling code here..
        //[/UserSliderCode_slider1]
    }
    else if (sliderThatWasMoved == slider2)
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3)
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainContentComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="450" initialHeight="150">
  <BACKGROUND backgroundColour="ffdddddd"/>
  <TEXTBUTTON name="undo button" id="9a41fb11475d83b5" memberName="undoButton"
              virtualName="" explicitFocusOrder="0" pos="16 16 200 24" buttonText="undo"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="redo button" id="bc8ecf33afbd3d28" memberName="redoButton"
              virtualName="" explicitFocusOrder="0" pos="232 16 200 24" buttonText="redo"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="slider 1" id="446f0ca249a2566b" memberName="slider1" virtualName=""
          explicitFocusOrder="0" pos="24 64 408 24" min="0" max="10" int="0"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider 2" id="b0d302ebdf77787b" memberName="slider2" virtualName=""
          explicitFocusOrder="0" pos="24 88 408 24" min="0" max="10" int="0"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="slider 3" id="e013c639a15bc6ad" memberName="slider3" virtualName=""
          explicitFocusOrder="0" pos="24 112 408 24" min="0" max="10" int="0"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
