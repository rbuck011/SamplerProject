/*
  ==============================================================================

    Mainbit.h
    Created: 25 May 2022 3:38:26pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SectionComp.h"

//==============================================================================
/*
*/
class Mainbit  : public juce::Component
{
public:
    Mainbit(NewProjectAudioProcessor& p);
    ~Mainbit() override;

    void paint (juce::Graphics&) override;
    void resized() override;


        TabbedComponent& getTabbedComponenet() { return *tabbedComponent; }
        Array<SectionComp*> getInstrumentViews() { return instruments; }
    private:
        NewProjectAudioProcessor& audioProcessor;
        std::unique_ptr<TabbedComponent> tabbedComponent;
        Array<SectionComp*> instruments;
      

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mainbit)
};
