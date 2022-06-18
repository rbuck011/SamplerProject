

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MySamplerSound.h"
#include "MySamplerVoice.h"
#include "SampleInstance.h"
//#include "WaveSamplerData.h"
//==============================================================================
/**
*/
class NewProjectAudioProcessor  : public AudioProcessor,
                                  public ValueTree::Listener
            
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //=====================================================
    
    
    
//    void loadFile();
//    void loadFile(const String& path);
//    get audio info, if the sound is playing
    int getSamplerSounds(){return mySampler.getNumSounds();}
   
    
//    
//    AudioBuffer<float>& getWaveform();
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    void setType(const int filtertype, const float cutoff, const float res);
    void updateADSRParams();
    void updateFilterParams();
    void updateParams();
//    void loadFile();
//    void loadFile(const String &path);
 
//
//    Synthesiser Samp;
   
//    AudioBuffer<float>&getWaveform();
    AudioProcessorValueTreeState& getValueTree(){return *APVTS;}
    std::unique_ptr<UndoManager> undoManager;
    std::unique_ptr<AudioProcessorValueTreeState> APVTS;
    
//    SampleInstance& getSampler() {return mySampler;}
private:
    
    
    SampleInstance mySampler;
    const int NumVoices {3};
    ADSRdata adsrData;
    FilterData filterData;
    
    
//    AudioFormatManager FormatManager;
//    AudioFormatReader* FormatReader{nullptr};
    

    
//    
//    AudioProcessorValueTreeState::ParameterLayout ParamLayout();
    void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged,const Identifier& property)override;
//
    std::atomic<bool> ShouldUpdate {false};




    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor)
    
};
