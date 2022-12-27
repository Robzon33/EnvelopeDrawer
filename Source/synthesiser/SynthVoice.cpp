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

    oscillators.add(new WavetableOscillator(sineTable, 1, 0.5f));
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    adsr.noteOn();

    for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size(); ++oscillatorIndex)
    {
        auto* oscillator = oscillators.getUnchecked(oscillatorIndex);
        oscillator->setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber), getSampleRate());
    }
}

void SynthVoice::stopNote(float, bool allowTailOff)
{
    adsr.noteOff();
}

void SynthVoice::pitchWheelMoved(int)
{
}

void SynthVoice::controllerMoved(int, int)
{
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    adsr.setParameters(adsrParams);

    while (--numSamples >= 0)
    {
        auto currentSample = 0.0f;

        for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size(); ++oscillatorIndex)
        {
            auto* oscillator = oscillators.getUnchecked(oscillatorIndex);
            currentSample += oscillator->getNextSample();
        }

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, currentSample * adsr.getNextSample());

        ++startSample;
    }
}

void SynthVoice::setADSRSampleRate(double sampleRate)
{
    adsr.setSampleRate(sampleRate);
}

void SynthVoice::setEnvelopeParams()
{
    adsrParams.attack = 2.5f;
    adsrParams.decay = 0.1f;
    adsrParams.sustain = 1.1f;
    adsrParams.release = 10.1f;

    adsr.setParameters(adsrParams);
}

void SynthVoice::addHarmonic()
{
    auto harmonic = oscillators.size() + 1;
    oscillators.add(new WavetableOscillator(sineTable, harmonic, defaultHarmonicWeight));
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
