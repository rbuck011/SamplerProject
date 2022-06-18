/*
  ==============================================================================

    MainControls.h
    Created: 13 May 2022 5:06:49pm
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

class TabControls : public Component
{
public:
    TabControls(NewProjectAudioProcessor& p);
    ~TabControls();

    void paint(Graphics& g) override;
    void resized() override;

    TabbedComponent& getTabControls() { return *tabComp;}
    Array<SectionComp*> getInstrumentViews() { return instruments; }
private:
    NewProjectAudioProcessor& audioProcessor;
    std::unique_ptr<TabbedComponent> tabComp;
    Array<SectionComp*>instruments;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TabControls)
};
