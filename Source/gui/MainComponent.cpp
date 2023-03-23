/*
  ==============================================================================

    MainComponent.cpp
    Created: 26 Dec 2022 5:59:52pm
    Author:  Toko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(Synth& s, int width)
    : synth(s)
{
    addOscButton.reset(new juce::TextButton("+"));
    addOscButton->addListener(this);
    addAndMakeVisible(addOscButton.get());

    deleteOscButton.reset(new juce::TextButton("-"));
    deleteOscButton->addListener(this);
    addAndMakeVisible(deleteOscButton.get());

    syncToggleButton.reset (new juce::ToggleButton ("Sync"));
    syncToggleButton->addListener (this);
    addAndMakeVisible (syncToggleButton.get ());

    setSize(width, 300);
    loadData();
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId).darker(0.5f));
}

void MainComponent::resized()
{
    auto b = getLocalBounds();

    auto buttonArea = b.removeFromTop(buttonsHeight);
    addOscButton->setBounds(buttonArea.removeFromLeft(40).reduced(3));
    deleteOscButton->setBounds(buttonArea.removeFromLeft(40).reduced(3));
    syncToggleButton->setBounds (buttonArea.removeFromRight (100).reduced (3));

    for (auto i = 0; i < oscComponents.size(); ++i)
    {
        oscComponents.getUnchecked(i)->setBounds(b.removeFromTop(oscComponentHeight));
    }
}

void MainComponent::buttonClicked(juce::Button* button)
{
    auto* synthVoice = dynamic_cast<SynthVoice*>(synth.getVoice(0));

    if (button == addOscButton.get())
    {
        synthVoice->addHarmonic();

        auto& oscillators = synthVoice->getOscillators();
        auto oscillator = oscillators.getUnchecked(oscillators.size() - 1);
        addNewOscillatorComponent(oscillator);
    }
    if (button == deleteOscButton.get())
    {
        synthVoice->deleteHarmonic();

		if (oscComponents.size() > 1)
			oscComponents.removeLast();

        setSize(getWidth(), getNewComponentHeight());
    }
    if (button == syncToggleButton.get ())
    {
        syncWithMain ();
    }
}

void MainComponent::loadData()
{
    if (oscComponents.size() > 0)
    {
        oscComponents.clear(true);
    }

    auto* synthVoice = dynamic_cast<SynthVoice*>(synth.getVoice(0));

    auto& oscillators = synthVoice->getOscillators();

    for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size(); ++oscillatorIndex)
    {
        auto oscillator = oscillators.getUnchecked(oscillatorIndex);      
        addNewOscillatorComponent(oscillator);
    }
}

void MainComponent::addNewOscillatorComponent(WavetableOscillator* oscillator)
{
    OscillatorComponent* newComponent = new OscillatorComponent(*oscillator);
    oscComponents.add(newComponent);
    addAndMakeVisible(newComponent);
    setSize(getWidth(), getNewComponentHeight());
}

int MainComponent::getNewComponentHeight()
{
    return oscComponents.size() * oscComponentHeight + buttonsHeight;
}

void MainComponent::syncWithMain ()
{
    auto* synthVoice = dynamic_cast<SynthVoice*>(synth.getVoice (0));

    auto& oscillators = synthVoice->getOscillators ();

    auto firstOsc = oscillators.getUnchecked (0);

    auto& envelopePointsToCopy = firstOsc->getEnvelope ().getPointVector ();

    for (auto oscillatorIndex = 1; oscillatorIndex < oscillators.size (); ++oscillatorIndex)
    {
        auto oscillator = oscillators.getUnchecked (oscillatorIndex);
        oscillator->getEnvelope ().setPointVector (envelopePointsToCopy);
    }
}
