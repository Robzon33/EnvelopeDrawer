/*
  ==============================================================================

    Synth.cpp
    Created: 14 Dec 2022 4:22:44pm
    Author:  Toko

  ==============================================================================
*/

#include "Synth.h"

Synth::Synth()
{
    this->clearVoices();

    auto numVoices = 1;
    for (auto i = 0; i < numVoices; ++i)
    {
        this->addVoice(new SynthVoice());
    }

    this->clearSounds();
    this->addSound(new SynthSound());
}

Synth::~Synth()
{
}
