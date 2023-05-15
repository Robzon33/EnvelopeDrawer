/*
  ==============================================================================

    SynthVoice.cpp
    Created: 19 Nov 2022 7:47:03pm
    Author:  Toko

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
{
    createWavetable();

    oscillators.add(new WavetableOscillator(sineTable, 1, 0.5f, getSampleRate ()));
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size(); ++oscillatorIndex)
    {
        auto* oscillator = oscillators.getUnchecked(oscillatorIndex);
        auto frequency = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        oscillator->setFrequency (frequency);
        oscillator->setAdsrNoteOn();
    }
}

void SynthVoice::stopNote(float, bool allowTailOff)
{
    for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size (); ++oscillatorIndex)
    {
        auto* oscillator = oscillators.getUnchecked (oscillatorIndex);
        oscillator->setAdsrNoteOff();
    }
}

void SynthVoice::pitchWheelMoved(int)
{
}

void SynthVoice::controllerMoved(int, int)
{
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    while (--numSamples >= 0)
    {
        auto currentSample = 0.0f;

        for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size(); ++oscillatorIndex)
        {
            auto* oscillator = oscillators.getUnchecked(oscillatorIndex);
            currentSample += oscillator->getNextSample();
        }

        for (auto i = outputBuffer.getNumChannels (); --i >= 0;)
        {
            outputBuffer.addSample (i, startSample, currentSample);
        }

        ++startSample;
    }
}

void SynthVoice::setSampleRate(double newSampleRate)
{
    for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size (); ++oscillatorIndex)
    {
        auto* oscillator = oscillators.getUnchecked (oscillatorIndex);
        oscillator->setSampleRate(newSampleRate);
    }
}

void SynthVoice::addHarmonic()
{
    auto harmonic = oscillators.size() + 1;
    oscillators.add(new WavetableOscillator(sineTable, harmonic, defaultHarmonicWeight, getSampleRate()));
}

void SynthVoice::deleteHarmonic()
{
	if (oscillators.size() > 0)
		oscillators.removeLast();
}

juce::OwnedArray<WavetableOscillator>& SynthVoice::getOscillators()
{
    return oscillators;
}

void SynthVoice::createWavetable()
{
    sineTable.setSize(1, (int)tableSize + 1);
    auto* samples = sineTable.getWritePointer(0);

    auto angleDelta = juce::MathConstants<double>::twoPi / (double)(tableSize - 1);
    auto currentAngle = 0.0;

    for (unsigned int i = 0; i < tableSize; ++i)
    {
        auto sample = std::sin(currentAngle);
        samples[i] = (float)sample;
        currentAngle += angleDelta;
    }

    samples[tableSize] = samples[0];
}
