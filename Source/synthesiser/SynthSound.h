/*
  ==============================================================================

    SynthSound.h
    Created: 19 Nov 2022 7:46:50pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    SynthSound();

    bool appliesToNote(int /*midiNoteNumber*/) override;
    bool appliesToChannel(int /*midiChannel*/) override;
};
