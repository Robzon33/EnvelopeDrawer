/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EnvelopeDrawerAudioProcessorEditor::EnvelopeDrawerAudioProcessorEditor (EnvelopeDrawerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    keyboardComponent.reset(new KeyboardComponent(*p.getMidiKeyboardState()));
    addAndMakeVisible(keyboardComponent.get());
    adsrComponent.reset(new ADSRComponent());
    addAndMakeVisible(adsrComponent.get());

    setSize (400, 300);
}

EnvelopeDrawerAudioProcessorEditor::~EnvelopeDrawerAudioProcessorEditor()
{
}

//==============================================================================
void EnvelopeDrawerAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void EnvelopeDrawerAudioProcessorEditor::resized()
{
    auto b = getLocalBounds();

    adsrComponent.get()->setBounds(b.removeFromTop(200));
    keyboardComponent.get()->setBounds(b);
}
