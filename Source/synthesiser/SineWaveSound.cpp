/*
  ==============================================================================

    SineWaveSound.cpp
    Created: 19 Nov 2022 7:46:50pm
    Author:  Toko

  ==============================================================================
*/

#include "SineWaveSound.h"

SineWaveSound::SineWaveSound()
{
}

bool SineWaveSound::appliesToNote(int)
{
    return true;
}

bool SineWaveSound::appliesToChannel(int)
{
    return true;
}
