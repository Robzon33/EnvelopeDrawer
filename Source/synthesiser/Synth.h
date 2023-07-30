/*
  ==============================================================================

    Synth.h
    Created: 14 Dec 2022 4:22:44pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

class Synth : public juce::Synthesiser
{
public:
    Synth();
    ~Synth();
    
    bool addHarmonic();
    bool deleteHarmonic();
    void setAdsrParams(int harmonic, float attack, float decay, float sustain, float release);
    juce::ADSR::Parameters& getAdsrParams(int harmonic);
    void setPitch(int harmonic, float pitch);
    float getPitch(int harmonic);
    void setWeight(int harmonic, float weight);
    float getWeight(int harmonic);
    int getNumberOfVoicesHarmonics();
private:
    juce::OwnedArray<juce::ADSR::Parameters> adsrParams;
    const int maxNumberOfHarmonics = 20;
    
    void applyAdsrParamsToVoices(int harmonic);
    void addDefaultAdsrParams();
    void deleteAdsrParams();
};
