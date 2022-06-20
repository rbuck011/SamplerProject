/*
  ==============================================================================

    SamplerVoice.h
    Created: 19 May 2022 11:19:19pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MySamplerSound.h"
#include "FilterData.h"
#include "ADSRdata.h"

class MySamplerVoice : public SamplerVoice, public AudioProcessorValueTreeState::Listener
                      
{
public:
    MySamplerVoice()
    {};
    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void setMidiNote(int note);
    bool playSound(int note) const;
    
    using SynthesiserVoice::renderNextBlock;
    void setCurrentPlaybackSampleRate(double newRate) override;
    
  
    void reset();
    
//    ADSRdata& getAdsr() { return adsr; }
 
    void updateParams (const int filterType, const float filterCutoff, const float filterResonance);
    void updateAttack(const float attack);
    void updateDecay(const float decay);
    void updateSustain(const float sustain);
    void updateRelease(const float release);
    
    void updateType(const int filtertype);
    void updateCutoff( const float cutoff);
    void updateRes( const float res);
    
    void parameterChanged (const String& parameterID, float newValue)override;
   
    
private:
    
    ADSRdata env;
    int index;
    int pitchVal;
    double SampRate;
    BigInteger midiNote;
    static constexpr int numChannelsToProcess { 2 };
    double pitchRatio = 0;
    double sourceSamplePosition = 0;
    float lgain = 0, rgain = 0;
    FilterData filter;

    JUCE_LEAK_DETECTOR (MySamplerVoice)
};
