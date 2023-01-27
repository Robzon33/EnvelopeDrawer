/*
  ==============================================================================

    OscillatorComponent.h
    Created: 26 Dec 2022 6:02:28pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../synthesiser/WavetableOscillator.h"
#include "EnvelopeComponent.h"

//==============================================================================
/*
*/
class OscillatorComponent  : public juce::Component,
    public juce::Slider::Listener
{
public:
    OscillatorComponent(WavetableOscillator&);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider);
private:
    WavetableOscillator& wavetableOscillator;

    std::unique_ptr<juce::Slider> pitchSlider;
    std::unique_ptr<juce::Slider> weightSlider;
    std::unique_ptr<juce::Slider> durationSlider;
    std::unique_ptr<juce::Slider> sustainPosSlider;

    std::unique_ptr<EnvelopeComponent> envelopeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
