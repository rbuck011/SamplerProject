/*
  ==============================================================================

    FilterData.cpp
    Created: 12 May 2022 12:15:25am
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include "FilterData.h"

FilterData::FilterData()
{
    setType(juce::dsp::StateVariableTPTFilterType::lowpass);
}

void FilterData::SetType (const int filterType){
    selectFilterType (filterType);
}
void FilterData::setCutoff(const float filterCutoff){
    setCutoffFrequency (filterCutoff);
}
void FilterData::setRes(const float filterResonance){
    setResonance (filterResonance);
}

void FilterData::setLfoParams (const float freq, const float depth)
{
//    lfoGain = juce::Decibels::gainToDecibels (depth);
//    lfo.setFrequency (freq);
}

void FilterData::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    prepare (spec);
}


void FilterData::selectFilterType (const int filterType)
{
    switch (filterType)
    {
        case 0:
            setType (juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
            
        case 1:
            setType (juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
            
        case 2:
            setType (juce::dsp::StateVariableTPTFilterType::highpass);
            break;
            
        default:
            setType (juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
    }
}

void FilterData::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block { buffer };
    process (juce::dsp::ProcessContextReplacing<float>(block));
}

float FilterData::processNextSample (int channel, float inputValue)
{
    return processSample (channel, inputValue);
}

void FilterData::resetAll()
{
    reset();
}
