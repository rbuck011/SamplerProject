
#include "SampleInstance.h"

#define NUM_VOICES 4


void SampleInstance::setup(){
    
    instruments = {"Sample_1","Sample_2","Sample_3","Sample_4"};
    
    for (int i = 0; i < NUM_VOICES; i++)
        {   auto* voice = new MySamplerVoice(i);

            switch(i)
            {
            case Sample_1:
                voice->setMidiNote(37);
                break;
            case Sample_2:
                voice->setMidiNote(38);
                break;
            case Sample_3:
                voice->setMidiNote(39);
                break;
            case Sample_4:
                voice->setMidiNote(40);
                break;
                default:
                break;
                }
               addVoice(voice);
        }
    FormatManager.registerBasicFormats();
    setPath();
}


void SampleInstance::noteOn(int midiChannel,
    int midiNoteNumber,
    float velocity)
{
    const ScopedLock sl(lock);
    
    for(int j = 0; j < getNumSounds(); j++)
    {
        auto* sound = getSound(j).get();
        if(sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
        {
            for(int i = 0; i < getNumVoices(); i++)
            {
                if(auto* voice = dynamic_cast<MySamplerVoice*>(getVoice(i)))
                {
                    if(voice->playSound(midiNoteNumber) && voice->getCurrentlyPlayingSound())
                    {
                        stopVoice(voice, 0.0f, false);
                    }
                    startVoice(voice, sound, midiChannel, midiNoteNumber, velocity);
                }
                
            }
       
        }
    }
}


void SampleInstance::setPath(){
    //I need to change the name of the input files to Sample_1, Sample_2 etc
    int midiNote = 37;
   
        String path = *pathh;
    
        if(path == String("Sample_1"))
        {
            midiNote = 37;
        }

        else if( path == String("Sample_2"))
        {
            midiNote = 38;
        }
        else if(path ==  String("Sample_3"))
        {
            midiNote = 39;
        }
        else if (path == String("Sample_4"))
        {
            midiNote = 40;
        }
        else
        {
            midiNote = -1;
        }
    
        auto file = File(path);
    
        String FileName = file.getFileNameWithoutExtension();
        std::unique_ptr<AudioFormatReader> reader(FormatManager.createReaderFor(file));
        BigInteger note;
        note.setBit(midiNote);
        double attackTimeSec = 0.1;
        double releaseTimeSec = 0.1;
        double maxSampleLength = 10.0;
        addSound(new MySamplerSound(path, *reader, note, midiNote, attackTimeSec, releaseTimeSec, maxSampleLength));

}
    
AudioBuffer<float>& SampleInstance::getWaveform()
{
    // get the last added synth sound as a SamplerSound*
    
    auto sound = dynamic_cast<MySamplerSound*>(getSound(getNumSounds()).get());
    if (sound)
    {
        return *sound->getAudioData();
    }
    // just in case it somehow happens that the sound doesn't exist or isn't a SamplerSound,
    // return a static instance of an empty AudioBuffer here...
    static AudioBuffer<float> dummybuffer;
   return dummybuffer;
  
}


void SampleInstance:: parameterChanged (const String& parameterID, float newValue){
    
    
}
