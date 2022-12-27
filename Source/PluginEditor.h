/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/KeyboardComponent.h"
#include "gui/MainComponent.h"

//==============================================================================
/**
*/
class EnvelopeDrawerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EnvelopeDrawerAudioProcessorEditor (EnvelopeDrawerAudioProcessor&);
    ~EnvelopeDrawerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EnvelopeDrawerAudioProcessor& audioProcessor;

    std::unique_ptr<KeyboardComponent> keyboardComponent;

    std::unique_ptr<MainComponent> mainComponent;
    std::unique_ptr<juce::Viewport> viewport;

    const int height = 800;
    const int width = 800;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeDrawerAudioProcessorEditor)
};
