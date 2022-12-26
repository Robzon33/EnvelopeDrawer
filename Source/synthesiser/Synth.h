/*
  ==============================================================================

    Synth.h
    Created: 14 Dec 2022 4:22:44pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

class Synth : public juce::Synthesiser
{
public:
    Synth();
    ~Synth();
private:
};