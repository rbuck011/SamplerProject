/*
  ==============================================================================

    FilterData.h
    Created: 12 May 2022 12:15:25am
    Author:  Rhys William Buckham

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class FilterData : public juce::dsp::StateVariableTPTFilter<float>
{
public:
    FilterData();
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void SetType (const int filterType);
    void setCutoff(const float filterCutoff);
    void setRes(const float filterResonance);
    void setLfoParams (const float freq, const float depth);
    void processNextBlock (juce::AudioBuffer<float>& buffer);
    float processNextSample (int channel, float inputValue);
    void resetAll();
    
private:
    void selectFilterType (const int type);
   
};
