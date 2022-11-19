/*
  ==============================================================================

    SineWaveSound.h
    Created: 19 Nov 2022 7:46:50pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SineWaveSound : public juce::SynthesiserSound
{
public:
    SineWaveSound();

    bool appliesToNote(int /*midiNoteNumber*/) override;
    bool appliesToChannel(int /*midiChannel*/) override;
};
