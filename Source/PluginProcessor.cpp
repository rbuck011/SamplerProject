
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations  //init list
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),APVTS(*this, nullptr, "PARAMETERS",ParamLayout())
                   
                        
#endif
{
        FormatManager.registerBasicFormats();
      
          
//        mySampler.addSound (new SamplerSound());
        for (int i = 0; i < NumVoices; i++)
        {
            mySampler.addVoice (new MySamplerVoice());
        }
    
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
    
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;  
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{


    mySampler.setCurrentPlaybackSampleRate(sampleRate);
    updateParams();

}


void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if(ShouldUpdate){
        updateParams();
    }
    
    mySampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor(*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
       MemoryOutputStream stream(destData, false);
        APVTS.state.writeToStream(stream);
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

    if(tree.isValid())
    {
        if(tree.hasType("PARAMETERS"))
        {
            APVTS.state = tree;
        }
    }
    
}


void NewProjectAudioProcessor::updateParams(){
    updateADSRParams();
    updateFilterParams();
}


void NewProjectAudioProcessor::updateADSRParams()
{


   ShouldUpdate = false;


    for(int i = 0; i < mySampler.getNumSounds();++i){

        if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler.getVoice(i))){

            auto& attack = *APVTS.getRawParameterValue("ATTACK");
            auto& decay = *APVTS.getRawParameterValue("DECAY");
            auto& sustain = *APVTS.getRawParameterValue("SUSTAIN");
            auto& release = *APVTS.getRawParameterValue("RELEASE");

            voice->updateAttack(attack.load());
            voice->updateDecay(decay.load());
            voice->updateSustain(sustain.load());
            voice->updateRelease(release.load());

          }

    }
}

void NewProjectAudioProcessor::updateFilterParams(){
    
    ShouldUpdate = false;
    
    for(int i = 0; i < mySampler.getNumSounds();++i){

        if(auto voice = dynamic_cast<MySamplerVoice*>(mySampler.getVoice(i))){

           auto& filterchoice = *APVTS.getRawParameterValue("FILTERCHOICE"+String(i));
            auto& freq = *APVTS.getRawParameterValue("CUTOFF"+String(i));
            auto& res = *APVTS.getRawParameterValue("RESONANCE"+String(i));
    
            voice->updateType(filterchoice.load());
            voice->updateCutoff(freq.load());
            voice->updateRes(res.load());
            
        }

  }
            
}


void NewProjectAudioProcessor::loadFile()
{
    mySampler.clearSounds();
    
    FileChooser chooser { "Please load a file" };
    
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        // the reader can be a local variable here since it's not needed by the SamplerSound after this
        std::unique_ptr<AudioFormatReader> reader{ FormatManager.createReaderFor(file) };
        if (reader)
        {
            BigInteger range;
            range.setRange(0, 128, true);
            mySampler.addSound(new MySamplerSound("Sample", *reader, range, 60, 0.1, 0.1, 10.0));
        }
        
    }
    
    
}

void NewProjectAudioProcessor::loadFile (const String& path)
{
    mySampler.clearSounds();
    
    auto file = File (path);
    // the reader can be a local variable here since it's not needed by the other classes after this
    std::unique_ptr<AudioFormatReader> reader{FormatManager.createReaderFor(file) };
    if (reader)
    {
        BigInteger range;
        range.setRange(0, 128, true);
        mySampler.addSound(new MySamplerSound("Sample", *reader, range, 60, 0.1, 0.1, 10.0));
//        updateADSR();
    }
    
}

AudioBuffer<float>& NewProjectAudioProcessor::getWaveForm()
{
    // get the last added synth sound as a SamplerSound*
    auto sound = dynamic_cast<MySamplerSound*>(mySampler.getSound(mySampler.getNumSounds() - 1).get());
    if (sound)
    {
        return *sound->getAudioData();
    }
    // just in case it somehow happens that the sound doesn't exist or isn't a SamplerSound,
    // return a static instance of an empty AudioBuffer here...
    static AudioBuffer<float> dummybuffer;
    return dummybuffer;
}


AudioProcessorValueTreeState::ParameterLayout NewProjectAudioProcessor::ParamLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<AudioParameterFloat>("ATTACK", "Attack", 0.0f, 5.0f, 0.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("DECAY", "Decay", 0.0f, 5.0f, 2.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("RELEASE", "Release", 0.0f, 5.0f, 0.0f));
    
    return { params.begin(), params.end() };
}







//void NewProjectAudioProcessor::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
//{
//    ShouldUpdate = true;
//}


void NewProjectAudioProcessor::updateADSR(const float attack, const float decay, const float sustain, const float release){
    adsrData.updateAttack(attack);
    adsrData.updateDecay(decay);
    adsrData.updateSustain(sustain);
    adsrData.updateRelease(release);
}



void NewProjectAudioProcessor::setType(const int filtertype, const float cutoff, const float res){
     
    filterData.SetType(filtertype);
    filterData.setCutoff(cutoff);
    filterData.setRes(res);
  
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}


