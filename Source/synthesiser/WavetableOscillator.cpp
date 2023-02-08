/*
  ==============================================================================

    WavetableOscillator.cpp
    Created: 25 Dec 2022 3:31:25pm
    Author:  Toko

  ==============================================================================
*/

#include "WavetableOscillator.h"

WavetableOscillator::WavetableOscillator(const juce::AudioSampleBuffer& wavetableToUse, int harmonic, float weight, double sampleRate)
      : wavetable(wavetableToUse),
        tableSize(wavetable.getNumSamples() - 1)
{
    this->harmonic = harmonic;
    this->weight = weight;
    this->pitch = 0;
    this->sampleRate = sampleRate;
    this->frequency = 0;

    envelope.reset(new Envelope(sampleRate));
}

WavetableOscillator::~WavetableOscillator()
{
}

void WavetableOscillator::setFrequency(double newFrequency)
{
    frequency = newFrequency;
    updateTableDelta ();
}

void WavetableOscillator::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
    updateTableDelta ();
    envelope.get ()->setSampleRate (sampleRate);
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

    currentSample *= weight;

    currentSample /= harmonic;

    auto envelopeValue = envelope->getNextSample ();

    currentSample *= envelopeValue;

    return currentSample;
}

float WavetableOscillator::getPitch()
{
    return pitch;
}

void WavetableOscillator::setPitch(float newPitch)
{
    pitch = newPitch;
}

float WavetableOscillator::getWeight()
{
    return weight;
}

void WavetableOscillator::setWeight(float newWeight)
{
    weight = newWeight;
}

Envelope& WavetableOscillator::getEnvelope()
{
    return *envelope;
}

void WavetableOscillator::updateTableDelta ()
{
    auto tableSizeOverSampleRate = (float) tableSize / sampleRate;
    auto pitchedFrequency = frequency + (frequency * pitch / 100);
    tableDelta = pitchedFrequency * harmonic * tableSizeOverSampleRate;
}
