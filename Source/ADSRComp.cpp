/*
  ==============================================================================

    ADSRComp.cpp
    Created: 13 Apr 2022 11:41:59pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include "ADSRComp.h"


//==============================================================================
ADSRComp::ADSRComp(NewProjectAudioProcessor& p) : audioProcessor(p)
  
{
    
    
    
    //Attack
//    AttackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
//    AttackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
//    AttackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
//    addAndMakeVisible(AttackSlider);
    //    //Decay
    //    DecaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    //    DecaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    //    DecaySlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    //    addAndMakeVisible(DecaySlider);
    
//    //Sustain
//    SustainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
//    SustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
//    SustainSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
//    addAndMakeVisible(SustainSlider);
    
    //    //Release
    //    ReleaseSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    //    ReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    //    ReleaseSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    //    addAndMakeVisible(ReleaseSlider);
    
    AttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(),"ATTACK",AttackSlider);
    DecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(),"DECAY",DecaySlider);
    SustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(),"SUSTAIN",SustainSlider);
    ReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(),"RELEASE",ReleaseSlider);
    
    setSliderParams(AttackSlider);
    setSliderParams(DecaySlider);
    setSliderParams(SustainSlider);
    setSliderParams(ReleaseSlider);
    
    setLabelParams(AttackLabel, "Attack", AttackSlider);
    setLabelParams(DecayLabel, "Decay", DecaySlider);
    setLabelParams(SustainLabel, "Sustain", SustainSlider);
    setLabelParams(ReleaseLabel, "Release", ReleaseSlider);
    
    
    
//    AttackLabel.setFont(10.0f);
//    AttackLabel.setText("Attack",NotificationType::dontSendNotification);
//    AttackLabel.setJustificationType(Justification::centredTop);
//    AttackLabel.attachToComponent(&AttackSlider, false);
//
//    DecayLabel.setFont(10.0f);
//    DecayLabel.setText("Decay",NotificationType::dontSendNotification);
//    DecayLabel.setJustificationType(Justification::centredTop);
//    DecayLabel.attachToComponent(&DecaySlider, false);
//
//    SustainLabel.setFont(10.0f);
//    SustainLabel.setText("Sustain",NotificationType::dontSendNotification);
//    SustainLabel.setJustificationType(Justification::centredTop);
//    SustainLabel.attachToComponent(&SustainSlider, false);
//
//    ReleaseLabel.setFont(10.0f);
//    ReleaseLabel.setText("Release",NotificationType::dontSendNotification);
//    ReleaseLabel.setJustificationType(Justification::centredTop);
//    ReleaseLabel.attachToComponent(&ReleaseSlider, false);
    
   
    
    
    
    
    
    
    
}

ADSRComp ::~ADSRComp ()
{
}

//==============================================================================
void ADSRComp ::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);
}

void ADSRComp ::resized()
{
//    const auto startX = 0.6f;
//    const auto startY = 0.2f;
//    const auto dialWidth = 0.1f;
//    const auto dialHeight = 0.75f;
//
//    AttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
//    DecaySlider.setBoundsRelative(startX+dialWidth,startY,dialWidth,dialHeight);
//    SustainSlider.setBoundsRelative(startX +(dialWidth * 2), startY, dialWidth, dialHeight);
//    ReleaseSlider.setBoundsRelative(startX+(dialWidth*3), startY, dialWidth, dialHeight);
//
    
    
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto SliderWidth = bounds.getWidth()/4-padding;
    const auto SliderHeight = bounds.getWidth()/4-padding;
    const auto SliderStartX = 0;
    const auto SliderStartY = bounds.getHeight()/2-(SliderHeight/2);
    
    AttackSlider.setBounds(SliderStartX,SliderStartY,SliderWidth,SliderHeight);
    DecaySlider.setBounds(AttackSlider.getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    SustainSlider.setBounds(DecaySlider.getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    ReleaseSlider.setBounds(SustainSlider.getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
}

void ADSRComp::setSliderParams(juce::Slider& slider){
    
    slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    slider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    addAndMakeVisible(slider);
    
}
void ADSRComp::setLabelParams(juce::Label& label,String lbl,juce::Slider& slider){
    
    label.setFont(10.0f);
    label.setText(lbl,NotificationType::dontSendNotification);
    label.setJustificationType(Justification::centredTop);
    label.attachToComponent(&slider, false);
}
