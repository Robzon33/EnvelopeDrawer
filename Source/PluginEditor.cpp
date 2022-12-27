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

    mainComponent.reset(new MainComponent(*p.getSynth(), width));
    addAndMakeVisible(mainComponent.get());
    viewport.reset(new juce::Viewport("MainComponentViewport"));
    addAndMakeVisible(viewport.get());
    viewport->setScrollBarsShown(true, false);
    viewport->setViewedComponent(mainComponent.get(), false);

    setSize (width, height);
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

    keyboardComponent.get()->setBounds(b.removeFromBottom(120));
    viewport.get()->setBounds(b);
}
