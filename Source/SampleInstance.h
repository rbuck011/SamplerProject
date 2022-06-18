/*
  ==============================================================================

    SampleInstance.h
    Created: 24 May 2022 3:58:58pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#pragma once
#include "MySamplerSound.h"
#include "MySamplerVoice.h"




class SampleInstance : public Synthesiser, public AudioProcessorValueTreeState::Listener
                       
{
    
    
    
public:
    void setup();
//    void update(const String& path);
    void parameterChanged (const String& parameterID, float newValue)override;
//    AudioBuffer<float>& getWaveform();
//    void loadFile(const String& path);
    void noteOn(int midiChannel,
                int midiNoteNumber,
                float velocity);
//    void setPath(const String& path);
    
    AudioBuffer<float>& getWaveform();
    void setPath();
private:
    
    static int counter;
    typedef enum Sounds {Sample_1 = 0, Sample_2, Sample_3,Sample_4} Sounds_t;
    String* pathh;
    StringArray instruments;
    AudioFormatManager FormatManager;
    File _files;
    AudioFormatReader* FormatReader{nullptr};

    
};

