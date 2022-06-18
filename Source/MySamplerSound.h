/*
  ==============================================================================

    SamplerSound.h
    Created: 19 May 2022 11:18:54pm
    Author:  Rhys William Buckham

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>


class MySamplerSound : public SamplerSound
{
public:
    friend class MySamplerVoice;
    
    MySamplerSound (const String& name,
                  AudioFormatReader& source,
                  const BigInteger& midiNotes,
                  int midiNoteForNormalPitch,
                  double attackTimeSecs,
                  double releaseTimeSecs,
                  double maxSampleLengthSeconds):
    
                  SamplerSound(name, source, midiNotes,
                  midiNoteForNormalPitch,
                  attackTimeSecs,releaseTimeSecs, maxSampleLengthSeconds),
                  sourceSampleRate(source.sampleRate), length(source.lengthInSamples),
                  midiRootNote(midiNoteForNormalPitch){}
    
    
    bool appliesToNote (int midiNoteNumber) override { return true;}
    bool appliesToChannel (int midiChannel) override { return true;}
    double getsourceSampleRate(){return sourceSampleRate;}
    int getmidiRootNote(){return midiRootNote;}
    long long getLength(){return length;}
    
    
private:
    //==============================================================================
    
    double sourceSampleRate;
    long long length;
    int midiRootNote;
    
    JUCE_LEAK_DETECTOR (MySamplerSound)

};
