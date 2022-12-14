/*
  ==============================================================================

    OscillatorComponent.cpp
    Created: 26 Dec 2022 6:02:28pm
    Author:  Toko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(WavetableOscillator& wto)
    : wavetableOscillator(wto)
{
    pitchSlider.reset(new juce::Slider());
    pitchSlider->setSliderStyle(juce::Slider::LinearVertical);
    pitchSlider->setRange(-10, 10, 0.1);
    pitchSlider->setValue(wavetableOscillator.getPitch());
    pitchSlider->setTextValueSuffix(" %");
    pitchSlider->addListener(this);
    addAndMakeVisible(pitchSlider.get());

    weightSlider.reset(new juce::Slider());
    weightSlider->setSliderStyle(juce::Slider::LinearVertical);
    weightSlider->setRange(0, 1.0, 0.01);
    weightSlider->setValue(wavetableOscillator.getWeight());
    weightSlider->addListener(this);
    addAndMakeVisible(weightSlider.get());

    durationSlider.reset(new juce::Slider());
    durationSlider->setSliderStyle(juce::Slider::LinearBar);
    durationSlider->setRange(0, 10, 0.01);
    durationSlider->setValue(wavetableOscillator.getEnvelope().getDuration());
    durationSlider->addListener(this);
    durationSlider->setTextValueSuffix(" sec");
    durationSlider->setTooltip("Define the envelopes duration");
    addAndMakeVisible(durationSlider.get());

    envelopeComponent.reset(new EnvelopeComponent(wavetableOscillator.getEnvelope()));
    addAndMakeVisible(envelopeComponent.get());
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void OscillatorComponent::resized()
{
    auto b = getLocalBounds().reduced(5);

    auto sliderArea = b.removeFromLeft(150);
    pitchSlider->setBounds(sliderArea.removeFromLeft(sliderArea.getWidth() / 2));
    weightSlider->setBounds(sliderArea);

    auto envelopeArea = b.removeFromLeft(500);
    envelopeComponent->setBounds(envelopeArea.removeFromTop(100));
    durationSlider->setBounds(envelopeArea);
}

void OscillatorComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == pitchSlider.get())
    {
        wavetableOscillator.setPitch(pitchSlider->getValue());
    }
    if (slider == weightSlider.get())
    {
        wavetableOscillator.setWeight(weightSlider->getValue());
    }
    if (slider == durationSlider.get())
    {
        wavetableOscillator.getEnvelope().setDuration(durationSlider->getValue());
        envelopeComponent.get ()->repaint ();
    }
}
