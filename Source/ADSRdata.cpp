
#include "ADSRdata.h"
void ADSRdata::setParams(){
    setParameters (adsrParams);
    
}

void ADSRdata::updateAttack (const float attack)
{
    adsrParams.attack = attack;
    setParams();

}

void ADSRdata::updateDecay(const float decay){
    adsrParams.decay = decay;
    setParams();
    
}

void ADSRdata::updateSustain(const float sustain)
{
    adsrParams.sustain = sustain;
    setParams();
   
    
}

void ADSRdata::updateRelease(const float release)
{
    adsrParams.release = release;
    setParams();
  
}


