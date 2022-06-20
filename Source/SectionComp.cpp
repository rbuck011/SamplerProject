/*
  ==============================================================================

    SectionComp.cpp
    Created: 13 May 2022 3:53:24pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SectionComp.h"

//==============================================================================
int SectionComp::counter = 0;

SectionComp::SectionComp(NewProjectAudioProcessor& p):
                             audioProcessor(p),
                             _Wave(p),
                             AttackSlider(new Slider("ATTACK")),
                             DecaySlider(new Slider("DECAY")),
                             SustainSlider(new Slider("SUSTAIN")),
                             ReleaseSlider(new Slider("RELEASE")),
                             CutOffSlider(new Slider("CUTOFF")),
                             ResSlider(new Slider("RESONANCE")),
                             ChooseFilter(new ComboBox("FILTERCHOICE")),
                             AttackAttachment(new AudioProcessorValueTreeState::SliderAttachment
                             (audioProcessor.getValueTree(), String("ATTACK"+String(counter)), *AttackSlider)),
                             DecayAttachment(new AudioProcessorValueTreeState::SliderAttachment
                             (audioProcessor.getValueTree(), String("DECAY"+String(counter)), *DecaySlider)),
                             SustainAttachment(new AudioProcessorValueTreeState::SliderAttachment
                             (audioProcessor.getValueTree(), String("SUSTAIN"+String(counter)), *SustainSlider)),
                             ReleaseAttachment(new AudioProcessorValueTreeState::SliderAttachment
                             (audioProcessor.getValueTree(), String("RELEASE"+String(counter)), *ReleaseSlider)),
                             FilterTypeAttachment(new AudioProcessorValueTreeState::ComboBoxAttachment
                             (audioProcessor.getValueTree(), String("FILTERCHOICE"+String(counter)), *ChooseFilter)),
                             CutOffAttachment(new AudioProcessorValueTreeState::SliderAttachment
                             (audioProcessor.getValueTree(), String("CUTOFF"+String(counter)), *CutOffSlider)),
                             ResAttachment(new AudioProcessorValueTreeState::SliderAttachment
                             (audioProcessor.getValueTree(), String("RESONANCE"+String(counter)), *ResSlider))
                             
                                                       
{
    
//
//    filter
//    CutOffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(),"CUTOFF",CutOffSlider);
//    ResAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(),"RESONANCE",ResSlider);
//    FilterTypeAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getValueTree(),"FILTERCHOICE",ChooseFilter);
    
    
    addAndMakeVisible(_Wave);
//    AttackSlider = std::make_unique<Slider>("ATTACK");
//    DecaySlider = std::make_unique<Slider>("DECAY");
//    SustainSlider = std::make_unique<Slider>("SUSTAIN");
//    ReleaseSlider = std::make_unique<Slider>("RELEASE");
//        AttackSlider->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
//        AttackSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
//        AttackSlider->setBounds(40, 120, 40, 136);
////        AttackSlider->setRange(0.0f, 500.0f);
//        AttackSlider->setValue(0.0f);
//        addAndMakeVisible(*AttackSlider);
//       std::cout<<AttackSlider->getValue();
       
    
    setSliderParams(AttackSlider);
    setSliderParams(DecaySlider);
    setSliderParams(SustainSlider);
    setSliderParams(ReleaseSlider);
    setSliderParams(CutOffSlider);
    setSliderParams(ResSlider);

    
//
//    setLabelParams(AttackLabel, "Attack", AttackSlider);
//    setLabelParams(DecayLabel, "Decay", DecaySlider);
//    setLabelParams(SustainLabel, "Sustain", SustainSlider);
//    setLabelParams(ReleaseLabel, "Release", ReleaseSlider);
//    setLabelParams(CutOffLabel, "Cutoff",CutOffSlider);
//    setLabelParams(ResLabel, "Cutoff",ResSlider);
    
  
    
    ChooseFilter->addItem("LowPass",1);
    ChooseFilter->addItem("HighPass",2);
    ChooseFilter->addItem("BandPass",3);
    ChooseFilter->setJustificationType(Justification::centred);
    addAndMakeVisible(*ChooseFilter);
    
    setSize(200,200);
    counter++;
}

SectionComp::~SectionComp()
{
    counter--;
}

void SectionComp::paint (juce::Graphics& g)
{
    g.fillAll(Colours::black);
}

void SectionComp::resized()
{
    //adsr
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 3;
    const auto SliderWidth = bounds.getWidth()/6-padding;
    const auto SliderHeight = bounds.getWidth()/6-padding;
    const auto SliderStartX = 0;
    const auto SliderStartY = bounds.getHeight()/2-(SliderHeight/2)+100;
    
    _Wave.setBounds(bounds);
//    const auto startX = 0.6f;
//    const auto startY = 0.2f;
//    const auto dialWidth = 0.1f;
//    const auto dialHeight = 0.75f;
    
    AttackSlider->setBounds(SliderStartX,SliderStartY,SliderWidth,SliderHeight);
    DecaySlider->setBounds(AttackSlider->getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    SustainSlider->setBounds(DecaySlider->getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    ReleaseSlider->setBounds(SustainSlider->getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    CutOffSlider->setBounds(ReleaseSlider->getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    ResSlider->setBounds(CutOffSlider->getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    ChooseFilter->setBounds(ResSlider->getRight()+padding,SliderStartY,SliderWidth,SliderHeight);
    

}
void SectionComp::setSliderParams(std::unique_ptr<Slider>& slider){

    slider->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    slider->setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    slider->setColour(Slider::ColourIds::thumbColourId, Colours::red);
    addAndMakeVisible(*slider);
   
    
}
//void SectionComp::setLabelParams(std::unique_ptr<Label>& label,String lbl,std::unique_ptr<Slider>& slider){
//
//    label->setFont(10.0f);
//    label->setText(lbl,NotificationType::dontSendNotification);
//    label->setJustificationType(Justification::centredTop);
////    label->attachToComponent(*slider, false);
//}
