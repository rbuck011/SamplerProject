#pragma once

#include <JuceHeader.h>

class ADSRdata : public juce::ADSR
{
public:
    void setParams();
    void updateAttack (const float attack);
    void updateDecay(const float decay);
    void updateSustain(const float sustain);
    void updateRelease(const float release);
private:
    juce::ADSR::Parameters adsrParams;
};
