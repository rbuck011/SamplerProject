/*
  ==============================================================================

    WaveDisplay.cpp
    Created: 13 Apr 2022 11:42:39pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include "WaveDisplay.h"

//==============================================================================
WaveDisplay::WaveDisplay(NewProjectAudioProcessor& p, int i) : audioProcessor (p), index(i)
{
    
    
}

WaveDisplay ::~WaveDisplay ()
{
    
    
}

//==============================================================================
void WaveDisplay ::paint (juce::Graphics& g)
{
    
    
    g.fillAll(Colours::azure.darker());
    
    auto waveform = _sample.getWaveform();
    
    if(waveform.getNumSamples() > 0)
    {
            Path p;
            AudioPoints.clear();
        
            
            auto ratio = waveform.getNumSamples() / getWidth();
            auto buffer = waveform.getReadPointer(0);
        
            
            //scale on x axis
            for(int i = 0; i <waveform.getNumSamples();i+=ratio){
                AudioPoints.push_back(buffer[i]);
            }
        
            g.setColour(Colours::yellow);
        
        
            p.startNewSubPath(0, getHeight()/2);
            
            
            // scale on y axis
            for(int i = 0; i < AudioPoints.size();++ i){
                auto point = jmap<float>(AudioPoints[i], -1.0f, 1.0f, getHeight(), 0);
                //scaled and connects the lines
                p.lineTo(i, point);
                
            }

            //actually draws the connected lines
            g.strokePath(p, PathStrokeType(2));
            
        g.setColour(Colours::white);
        g.setFont(15.0f);
        auto txtBounds = getLocalBounds().reduced(10, 10);
        g.drawFittedText(FileName, txtBounds, Justification::topRight, 1);
            
    }
    else
    {
        g.setColour(Colours::white);
        g.setFont(40.0f);
        g.drawFittedText("Drop an Audio File", getLocalBounds(), Justification::centred, 1);
    }
   
}


void WaveDisplay ::resized()
{
  
    
}

bool WaveDisplay::isInterestedInFileDrag(const StringArray &files){
    // is it an audio file?
    for(auto file : files){
        if(file.contains(".wav") || file.contains("mp3")||file.contains(".aif")){
        
            //if yes go
            return true;
        }
    }
    return false;
}

void WaveDisplay::filesDropped(const StringArray& files,
                                                  int x, int y){
    
    for(auto file:files){
        if(isInterestedInFileDrag(file)){
            
            auto myFile = std::make_unique<File>(file);
            FileName = myFile->getFileNameWithoutExtension();
         
            renameFile(file, "Sample_");

            _sample.settPath(file + String(index));
          }
    }
    repaint();
}


 




