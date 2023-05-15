/*
  ==============================================================================

    WavetableOscillator.h
    Created: 25 Dec 2022 3:31:25pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WavetableOscillator
{
public:
    WavetableOscillator(const juce::AudioSampleBuffer& wavetableToUse, int harmonic, float weight, double sampleRate);
    ~WavetableOscillator();

    void setFrequency(double newFrequency);
    void setSampleRate (double newSampleRate);
    float getNextSample() noexcept;

    float getPitch();
    void setPitch(float newPitch);
    float getWeight();
    void setWeight(float newWeight);
    
    void setAdsrParams(float attack, float decay, float sustain, float release);
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    void setAdsrNoteOn();
    void setAdsrNoteOff();
private:
    const juce::AudioSampleBuffer& wavetable;
    const int tableSize;
    float currentIndex = 0.0f;
    float tableDelta = 0.0f;
    int harmonic;
    float pitch;
    float weight;
    double sampleRate;
    double frequency;
   

    void updateTableDelta ();
};
