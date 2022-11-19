/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "gui/KeyboardComponent.h"
#include "gui/ADSRComponent.h"

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
    std::unique_ptr<ADSRComponent> adsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeDrawerAudioProcessorEditor)
};
