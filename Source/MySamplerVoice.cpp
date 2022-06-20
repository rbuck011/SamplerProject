/*
  ==============================================================================

    SamplerVoice.cpp
    Created: 19 May 2022 11:19:19pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include "MySamplerVoice.h"

bool MySamplerVoice::canPlaySound (SynthesiserSound* s)
{
    return dynamic_cast<const MySamplerSound*>(s) != nullptr;
}

void MySamplerVoice::startNote (int midiNoteNumber, float velocity,SynthesiserSound* s, int currentPitchWheelPosition)
{

    if (auto* sound = dynamic_cast<MySamplerSound*> (s))
    {
//        pitchRatio = std::pow (2.0, (midiNoteNumber - sound->getmidiRootNote()) / 12.0)
//                        * sound->getsourceSampleRate() / getSampleRate();

        sourceSamplePosition = 0.0;
        lgain = velocity;
        rgain = velocity;
        
        env.noteOn();
    

    }
    else
    {
        jassertfalse; // this object can only play SamplerSounds!
    }
    
    

    }

void MySamplerVoice::stopNote (float velocity, bool allowTailOff)
{
 
    if (allowTailOff)
    {
        env.noteOff();
    }
    else
    {
        clearCurrentNote();
        
    }
    }




void MySamplerVoice::controllerMoved (int controllerNumber, int newControllerValue)
{

}

void MySamplerVoice::pitchWheelMoved (int newPitchWheelValue)
{

}

void MySamplerVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();
    
//    envelopegen.setSampleRate (sampleRate);
   
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    for (int ch = 0; ch < numChannelsToProcess; ch++)
    {

//        filter[ch].prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
    
    }

    
   
}
void MySamplerVoice::setMidiNote(int note){midiNote.setBit(note);}
bool MySamplerVoice::playSound(int note)const{return midiNote[note];}


void MySamplerVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    if (auto* playingSound = static_cast<MySamplerSound*>(getCurrentlyPlayingSound().get()))
    {
        auto& data = *playingSound->getAudioData();
        const float* const inL = data.getReadPointer (0);
        const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer (1) : nullptr;

        float* outL = outputBuffer.getWritePointer (0, startSample);
        float* outR = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer (1, startSample) : nullptr;

        while (--numSamples >= 0)
        {
            auto pos = (int) sourceSamplePosition;
            auto alpha = (float) (sourceSamplePosition - pos);
            auto invAlpha = 1.0f - alpha;
          
            float envelopeValue = 0.0f;
            // just using a very simple linear interpolation here..
            float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
            float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
                                       : l;

            envelopeValue = env.getNextSample();

            l *= lgain * envelopeValue;
            r *= rgain * envelopeValue;

            if (outR != nullptr)
            {
                *outL++ += l;
                *outR++ += r;
            }
            else
            {
                *outL++ += (l + r) * 0.5f;
            }

            sourceSamplePosition += pitchRatio;

            if (sourceSamplePosition > playingSound->getLength()) 
            {
                stopNote (0.0f, false);
                break;
            }
        }
    }
    
  
}

void MySamplerVoice::reset()
{

   
}
void MySamplerVoice::updateAttack(const float attack){
    
    if (auto* sound = static_cast<SamplerSound*>(getCurrentlyPlayingSound().get())){
        env.updateAttack(attack);
    }
}

void MySamplerVoice::updateDecay(const float decay){

    if (auto* sound = static_cast<SamplerSound*>(getCurrentlyPlayingSound().get())){
        env.updateDecay(decay);
    }
}

void MySamplerVoice::updateSustain(const float sustain){

    if (auto* sound = static_cast<SamplerSound*>(getCurrentlyPlayingSound().get())){
        env.updateSustain(sustain);
    }
}

void MySamplerVoice::updateRelease (const float release){

    if (auto* sound = static_cast<SamplerSound*>(getCurrentlyPlayingSound().get())){
        env.updateRelease(release);
    }
}


void MySamplerVoice::updateType(const int filtertype){
    
    filter.SetType(filtertype);
}

void MySamplerVoice::updateCutoff( const float cutoff){
    
    filter.setCutoff(cutoff);
}

void MySamplerVoice::updateRes( const float res){
    
    filter.setRes(res);
}


void MySamplerVoice::parameterChanged(const String &parameterID, float newValue){
    
    if (parameterID == String("ATTACK"))
        {
            updateAttack(newValue);
           
        }
    if (parameterID == String("DECAY"))
        {
            updateDecay(newValue);
        }
    if (parameterID == String("SUSTAIN"))
        {
            updateSustain(newValue);
        }
    if (parameterID == String("RELEASE"))
        {
            updateRelease(newValue);
        }
    if (parameterID == String("FILTERCHOICE"))
        {
            updateType(newValue);
        }
    if (parameterID == String("CUTOFF"))
        {
            updateCutoff(newValue);
        }
    if (parameterID == String("RES"))
        {
            updateRes(newValue);
        }
}

void MySamplerVoice::updateParams (const int filterType, const float filterCutoff, const float filterResonance)
{
   
    for (int ch = 0; ch < numChannelsToProcess; ++ch)
    {
//        filter[ch].setParams(filterType, filterCutoff, filterResonance);
    
    }
    

}

void MySamplerVoice::setCurrentPlaybackSampleRate(double newRate){
    {
        SamplerVoice::setCurrentPlaybackSampleRate(newRate);
        if (SampRate != newRate && newRate != 0)
        {
            SampRate = newRate;
            env.setSampleRate(SampRate);
        }
    }
}
