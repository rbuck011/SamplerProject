/*
  ==============================================================================

    Mainbit.cpp
    Created: 25 May 2022 3:38:26pm
    Author:  Rhys William Buckham

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Mainbit.h"

//==============================================================================
Mainbit::Mainbit(NewProjectAudioProcessor& p) : audioProcessor(p), 
                                                tabbedComponent(new TabbedComponent(TabbedButtonBar::TabsAtTop))
{
    for(int i = 0; i < 4; i++)
        {
            instruments.add(new SectionComp(p));
        }

        tabbedComponent->addTab(translate("Sample_1"), Colours::lightgrey, instruments[0], true);
        tabbedComponent->addTab(translate("Sample_2"), Colours::lightgrey, instruments[1], true);
        tabbedComponent->addTab(translate("Sample_3"), Colours::lightgrey, instruments[2], true);
        tabbedComponent->addTab(translate("Sample_4"), Colours::lightgrey, instruments[3], true);
        tabbedComponent->setTabBarDepth(25);
        tabbedComponent->setCurrentTabIndex(0);

        setSize(600, 400);
        tabbedComponent->setBounds(0, 0, 600, 400);

        addAndMakeVisible(*tabbedComponent);
    
}

Mainbit::~Mainbit()
{
    instruments.clear();
}

void Mainbit::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

}
void Mainbit::resized()
{
   

}
