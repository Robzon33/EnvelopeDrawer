/*
  ==============================================================================

    AdsrComponent.h
    Created: 24 Apr 2023 3:53:47pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../synthesiser/Synth.h"

//==============================================================================
/*
*/
class AdsrComponent  :  public juce::Component,
                        public juce::Slider::Listener
{
public:
    AdsrComponent(Synth& s, int harmonic);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
private:
    Synth& synth;
    int harmonic;
    
    std::unique_ptr<juce::Slider> attackSlider;
    std::unique_ptr<juce::Slider> decaySlider;
    std::unique_ptr<juce::Slider> sustainSlider;
    std::unique_ptr<juce::Slider> releaseSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
