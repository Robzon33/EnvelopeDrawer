/*
  ==============================================================================

    MySynth.cpp
    Created: 14 Dec 2022 4:22:44pm
    Author:  Toko

  ==============================================================================
*/

#include "MySynth.h"

MySynth::MySynth()
{
    this->clearVoices();

    auto numVoices = 1;
    for (auto i = 0; i < numVoices; ++i)
    {
        this->addVoice(new SineWaveVoice());
    }

    this->clearSounds();
    this->addSound(new SineWaveSound());
}

MySynth::~MySynth()
{
}
