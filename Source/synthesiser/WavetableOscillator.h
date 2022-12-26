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
    WavetableOscillator(const juce::AudioSampleBuffer& wavetableToUse, int harmonic, float weight);
    ~WavetableOscillator();

    void setFrequency(float frequency, float sampleRate);
    float getNextSample() noexcept;
private:
    const juce::AudioSampleBuffer& wavetable;
    const int tableSize;
    float currentIndex = 0.0f;
    float tableDelta = 0.0f;
    int harmonic;
    float weight;
};