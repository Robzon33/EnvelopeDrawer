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

    auto numVoices = 6;
    for (auto i = 0; i < numVoices; ++i)
    {
        this->addVoice(new SynthVoice());
    }

    this->clearSounds();
    this->addSound(new SynthSound());
    
    addDefaultAdsrParams();
    applyAdsrParamsToVoices(0);
}

Synth::~Synth()
{
}

bool Synth::addHarmonic()
{
    if(adsrParams.size() < maxNumberOfHarmonics)
    {
        for (auto i = 0; i < getNumVoices(); ++i)
        {
            auto* synthVoice = dynamic_cast<SynthVoice*>(this->getVoice(i));
            synthVoice->addHarmonic();
        }
        this->addDefaultAdsrParams();
        this->applyAdsrParamsToVoices(adsrParams.size() - 1);
        return true;
    }
    return false;
}

bool Synth::deleteHarmonic()
{
    if(adsrParams.size() > 1)
    {
        for (auto i = 0; i < getNumVoices(); ++i)
        {
            auto* synthVoice = dynamic_cast<SynthVoice*>(this->getVoice(i));
            synthVoice->deleteHarmonic();
        }
        this->deleteAdsrParams();
        return true;
    }
    return false;
}

void Synth::setAdsrParams(int harmonic, float attack, float decay, float sustain, float release)
{
    auto* params = adsrParams.getUnchecked(harmonic);
    params->attack = attack;
    params->decay = decay;
    params->sustain = sustain;
    params->release = release;
    
    this->applyAdsrParamsToVoices(harmonic);
}

juce::ADSR::Parameters& Synth::getAdsrParams(int harmonic)
{
    return *adsrParams.getUnchecked(harmonic);
}

void Synth::setPitch(int harmonic, float pitch)
{
    for (auto i = 0; i < getNumVoices(); ++i)
    {
        auto* synthVoice = dynamic_cast<SynthVoice*>(this->getVoice(i));
        synthVoice->setPitch(harmonic, pitch);
    }
}

float Synth::getPitch(int harmonic)
{
    auto* synthVoice = dynamic_cast<SynthVoice*>(this->getVoice(0));
    return synthVoice->getOscillators().getUnchecked(harmonic)->getPitch();
}

void Synth::setWeight(int harmonic, float weight)
{
    for (auto i = 0; i < getNumVoices(); ++i)
    {
        auto* synthVoice = dynamic_cast<SynthVoice*>(this->getVoice(i));
        synthVoice->setWeight(harmonic, weight);
    }
}

float Synth::getWeight(int harmonic)
{
    auto* synthVoice = dynamic_cast<SynthVoice*>(this->getVoice(0));
    return synthVoice->getOscillators().getUnchecked(harmonic)->getWeight();
}

int Synth::getNumberOfVoicesHarmonics()
{
    return dynamic_cast<SynthVoice*>(this->getVoice(0))->getNumberOfHarmonics();
}

void Synth::applyAdsrParamsToVoices(int harmonic)
{
    auto attack = adsrParams.getUnchecked(harmonic)->attack;
    auto decay = adsrParams.getUnchecked(harmonic)->decay;
    auto sustain = adsrParams.getUnchecked(harmonic)->sustain;
    auto release = adsrParams.getUnchecked(harmonic)->release;
    
    for (auto i = 0; i < getNumVoices(); ++i)
    {
        auto* synthVoice = dynamic_cast<SynthVoice*>(this->getVoice(i));
        synthVoice->setAdsrParams(harmonic, attack, decay, sustain, release);
    }
}

void Synth::addDefaultAdsrParams()
{
    juce::ADSR::Parameters* params = new juce::ADSR::Parameters();
    params->attack = 0.8;
    params->decay = 0.3;
    params->sustain = 0.7;
    params->release = 0.4;
    
    adsrParams.add(params);
}

void Synth::deleteAdsrParams()
{
    if(adsrParams.size() > 0)
    {
        adsrParams.removeLast();
    }
}
