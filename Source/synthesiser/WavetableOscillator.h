/*
  ==============================================================================

    WavetableOscillator.h
    Created: 25 Dec 2022 3:31:25pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Envelope.h"

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
    Envelope& getEnvelope();
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
    std::unique_ptr<Envelope> envelope;

    void updateTableDelta ();
};