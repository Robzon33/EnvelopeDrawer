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

    // Overriding SynthesiserVoice functions
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote(float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    /*
     Sets sample rate.
     */
    void setSampleRate(double newSampleRate);
    
    /*
     Renders the next block. This function is called by the audio thread.
     */
    using SynthesiserVoice::renderNextBlock;

    /*
     Adds a further harmonic.
     */
    void addHarmonic();
    
    /*
     Deletes the last harmonic in the array.
     */
    void deleteHarmonic();
    
    /*
     Returns the current oscillator array.
     */
    juce::OwnedArray<WavetableOscillator>& getOscillators();
    
    /*
     Sets ADSR parameters for a given harmonic.
     */
    void setAdsrParams(int harmonic, float attack, float decay, float sustain, float release);
    
    /*
     Sets a new pitch for a given harmonic.
     */
    void setPitch(int harmonic, float pitch);
    
    /*
     Sets a new weight for a given harmonic.
     */
    void setWeight(int harmonic, float weight);
    
    /*
     Returns the synths voices number of harmonics, which is equal the number of elements
     in the oscillator array reduced by one (because the first oscillator represents the
     base note).
     */
    int getNumberOfHarmonics();
private:
    double currentAngle = 0.0;
    double angleDelta = 0.0;
    double level = 0.0;
    const float defaultHarmonicWeight = 0.2f;
    const int maxHarmonics = 20;

    const unsigned int tableSize = 1 << 7;
    juce::AudioSampleBuffer sineTable;
    juce::OwnedArray<WavetableOscillator> oscillators;
    
    /*
     Creates the wavetable for waveshaping synthesis.
     */
    void createWavetable();
};
