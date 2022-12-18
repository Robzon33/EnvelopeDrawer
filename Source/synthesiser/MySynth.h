/*
  ==============================================================================

    MySynth.h
    Created: 14 Dec 2022 4:22:44pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SineWaveSound.h"
#include "SineWaveVoice.h"

class MySynth : public juce::Synthesiser
{
public:
    MySynth();
    ~MySynth();
private:
};