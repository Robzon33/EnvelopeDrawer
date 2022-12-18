/*
  ==============================================================================

    SineWaveVoice.cpp
    Created: 19 Nov 2022 7:47:03pm
    Author:  Toko

  ==============================================================================
*/

#include "SineWaveVoice.h"

SineWaveVoice::SineWaveVoice()
{
}

bool SineWaveVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SineWaveSound*> (sound) != nullptr;
}

void SineWaveVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    adsr.noteOn();

    currentAngle = 0.0;
    level = velocity * 0.15;

    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    angleDelta = cyclesPerSample * juce::MathConstants<double>::twoPi;
}

void SineWaveVoice::stopNote(float, bool allowTailOff)
{
    adsr.noteOff();
}

void SineWaveVoice::pitchWheelMoved(int)
{
}

void SineWaveVoice::controllerMoved(int, int)
{
}

void SineWaveVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    adsr.setParameters(adsrParams);

    while (--numSamples >= 0)
    {
        auto currentSample = (float)(std::sin(currentAngle) * level);
        auto adsrCurrentSample = adsr.getNextSample();

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, adsrCurrentSample * currentSample);

        currentAngle += angleDelta;
        ++startSample;
    }
}

void SineWaveVoice::setADSRSampleRate(double sampleRate)
{
    adsr.setSampleRate(sampleRate);
}

void SineWaveVoice::setEnvelopeParams()
{
    adsrParams.attack = 0.5f;
    adsrParams.decay = 0.1f;
    adsrParams.sustain = 1.1f;
    adsrParams.release = 10.1f;

    adsr.setParameters(adsrParams);
}
