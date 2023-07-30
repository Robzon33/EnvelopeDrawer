/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 24 Apr 2023 3:53:47pm
    Author:  Tobias Koelker

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(Synth& s, int harmonic)
: synth(s)
{
    this->harmonic = harmonic;
    
    juce::ADSR::Parameters params = synth.getAdsrParams(harmonic);
    
    attackSlider.reset(new juce::Slider());
    attackSlider->setSliderStyle(juce::Slider::LinearVertical);
    attackSlider->setRange(0, 5, 0.05);
    attackSlider->setValue(params.attack);
    attackSlider->setTextValueSuffix(" s");
    attackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    attackSlider->addListener(this);
    addAndMakeVisible(attackSlider.get());
    
    decaySlider.reset(new juce::Slider());
    decaySlider->setSliderStyle(juce::Slider::LinearVertical);
    decaySlider->setRange(0, 5, 0.05);
    decaySlider->setValue(params.decay);
    decaySlider->setTextValueSuffix(" s");
    decaySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    decaySlider->addListener(this);
    addAndMakeVisible(decaySlider.get());
    
    sustainSlider.reset(new juce::Slider());
    sustainSlider->setSliderStyle(juce::Slider::LinearVertical);
    sustainSlider->setRange(0, 1, 0.05);
    sustainSlider->setValue(params.sustain);
    sustainSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    sustainSlider->addListener(this);
    addAndMakeVisible(sustainSlider.get());
    
    releaseSlider.reset(new juce::Slider());
    releaseSlider->setSliderStyle(juce::Slider::LinearVertical);
    releaseSlider->setRange(0, 5, 0.05);
    releaseSlider->setValue(params.release);
    releaseSlider->setTextValueSuffix(" s");
    releaseSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    releaseSlider->addListener(this);
    addAndMakeVisible(releaseSlider.get());
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::yellow);
    
    g.drawRoundedRectangle(getLocalBounds().reduced(10).toFloat(), 3.0f, 2.0f);
}

void AdsrComponent::resized()
{
    auto sliderArea = getLocalBounds().reduced(20);
    
    auto amount = sliderArea.getWidth() / 4;
    
    attackSlider->setBounds (sliderArea.removeFromLeft (amount));
    decaySlider->setBounds (sliderArea.removeFromLeft (amount));
    sustainSlider->setBounds (sliderArea.removeFromLeft (amount));
    releaseSlider->setBounds (sliderArea.removeFromLeft (amount));
}

void AdsrComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == attackSlider.get() || slider == decaySlider.get()
        || slider == sustainSlider.get() || slider == releaseSlider.get())
    {
        synth.setAdsrParams(this->harmonic,
                            attackSlider->getValue(),
                            decaySlider->getValue(),
                            sustainSlider->getValue(),
                            releaseSlider->getValue());
    }
}
