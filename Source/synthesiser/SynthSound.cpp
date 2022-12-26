/*
  ==============================================================================

    SynthSound.cpp
    Created: 19 Nov 2022 7:46:50pm
    Author:  Toko

  ==============================================================================
*/

#include "SynthSound.h"

SynthSound::SynthSound()
{
}

bool SynthSound::appliesToNote(int)
{
    return true;
}

bool SynthSound::appliesToChannel(int)
{
    return true;
}
