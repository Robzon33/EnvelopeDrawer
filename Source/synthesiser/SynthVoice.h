/*
  ==============================================================================

    SynthVoice.h
    Created: 19 Nov 2022 7:47:03pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "WavetableOscillator.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    SynthVoice();

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote(float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void setADSRSampleRate(double sampleRate);
    void setEnvelopeParams();

    using SynthesiserVoice::renderNextBlock;

    void addHarmonic(int harmonic, float weight);
    void deleteHarmonic(int index);
private:
    double currentAngle = 0.0;
    double angleDelta = 0.0;
    double level = 0.0;

    const unsigned int tableSize = 1 << 7;
    juce::AudioSampleBuffer sineTable;
    juce::OwnedArray<WavetableOscillator> oscillators;

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    void createWavetable();
};