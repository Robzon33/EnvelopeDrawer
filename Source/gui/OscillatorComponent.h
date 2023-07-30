/*
  ==============================================================================

    OscillatorComponent.h
    Created: 26 Dec 2022 6:02:28pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../synthesiser/Synth.h"
#include "../synthesiser/WavetableOscillator.h"
#include "AdsrComponent.h"

//==============================================================================
/*
*/
class OscillatorComponent  : public juce::Component,
    public juce::Slider::Listener
{
public:
    OscillatorComponent(Synth& s, int harmonic);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
private:
    Synth& synth;
    int harmonic;

    std::unique_ptr<juce::Slider> pitchSlider;
    std::unique_ptr<juce::Slider> weightSlider;
    
    std::unique_ptr<AdsrComponent> adsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
