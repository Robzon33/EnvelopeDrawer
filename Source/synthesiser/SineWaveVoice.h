/*
  ==============================================================================

    SineWaveVoice.h
    Created: 19 Nov 2022 7:47:03pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SineWaveSound.h"

class SineWaveVoice : public juce::SynthesiserVoice
{
public:
    SineWaveVoice();

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote(float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void setADSRSampleRate(double sampleRate);
    void setEnvelopeParams();

    using SynthesiserVoice::renderNextBlock;
private:
    double currentAngle = 0.0;
    double angleDelta = 0.0;
    double level = 0.0;

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
};