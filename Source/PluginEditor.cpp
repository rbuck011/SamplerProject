/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      _main(p)
{
 
    addAndMakeVisible(_main);
    
   
    startTimerHz (30);
    setSize(1000, 800);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
// (Our component is opaque, so we must completely fill the background with a solid colour)
    if(audioProcessor.getSamplerSounds() > 0){
        g.fillAll(Colours::red);
    }
    else
    {
        g.fillAll(Colours::blue);
    }
    
}

void NewProjectAudioProcessorEditor::resized()
{

     auto r = getLocalBounds();
    _main.setBounds(r);
    
}

void NewProjectAudioProcessorEditor::timerCallback()
{
   repaint();
}
