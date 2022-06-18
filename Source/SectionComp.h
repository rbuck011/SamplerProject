/*
  ==============================================================================

    SectionComp.h
    Created: 13 May 2022 3:53:24pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveDisplay.h"

//==============================================================================
/*
*/
class SectionComp  : public Component
{
public:
     SectionComp(NewProjectAudioProcessor& p);
    ~SectionComp();

    void paint (Graphics&) override;
    void resized() override;
    void setSliderParams(std::unique_ptr<Slider>& Slider);
    void setLabelParams(std::unique_ptr<Label>& label,String lbl,std::unique_ptr<Slider>& slider);

private:
    static int counter;
    
    NewProjectAudioProcessor& audioProcessor;
    WaveDisplay _Wave;
    //adsr
//    Slider AttackSlider, DecaySlider, SustainSlider, ReleaseSlider;
//    Label AttackLabel, DecayLabel, SustainLabel, ReleaseLabel;
    
    std::unique_ptr<Slider> AttackSlider;
    std::unique_ptr<Slider> DecaySlider;
    std::unique_ptr<Slider> SustainSlider;
    std::unique_ptr<Slider> ReleaseSlider;
    std::unique_ptr<Slider> CutOffSlider;
    std::unique_ptr<Slider> ResSlider;
    std::unique_ptr<ComboBox> ChooseFilter;
//    std::unique_ptr<Label>AttackLabel, DecayLabel, SustainLabel, ReleaseLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>AttackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>DecayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>SustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>ReleaseAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>FilterTypeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>CutOffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>ResAttachment;
    
//    NewProjectAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SectionComp)
    
    
    
};
