/*
  ==============================================================================

    WavetableOscillator.cpp
    Created: 25 Dec 2022 3:31:25pm
    Author:  Toko

  ==============================================================================
*/

#include "WavetableOscillator.h"

WavetableOscillator::WavetableOscillator(const juce::AudioSampleBuffer& wavetableToUse, int harmonic, float weight)
      : wavetable(wavetableToUse),
        tableSize(wavetable.getNumSamples() - 1)
{
    this->harmonic = harmonic;
    this->weight = weight;
}

WavetableOscillator::~WavetableOscillator()
{
}

void WavetableOscillator::setFrequency(float frequency, float sampleRate)
{
    auto tableSizeOverSampleRate = (float)tableSize / sampleRate;
    tableDelta = frequency * harmonic * tableSizeOverSampleRate;
}

float WavetableOscillator::getNextSample() noexcept
{
    auto index0 = (unsigned int)currentIndex;
    auto index1 = index0 + 1;

    auto frac = currentIndex - (float)index0;
    
    auto* table = wavetable.getReadPointer(0);
    auto value0 = table[index0];
    auto value1 = table[index1];

    auto currentSample = value0 + frac * (value1 - value0);

    if ((currentIndex += tableDelta) > (float)tableSize)
        currentIndex -= (float)tableSize;

    return currentSample * weight;
}
