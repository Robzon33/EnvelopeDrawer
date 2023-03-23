/*
  ==============================================================================

    MainComponent.h
    Created: 26 Dec 2022 5:59:52pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscillatorComponent.h"
#include "../synthesiser/Synth.h"

//==============================================================================
/*
*/
class MainComponent  : public juce::Component,
    public juce::Button::Listener
{
public:
    MainComponent(Synth& s, int width);
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
private:
    Synth& synth;
    juce::OwnedArray<OscillatorComponent> oscComponents;
    std::unique_ptr<juce::TextButton> addOscButton;
    std::unique_ptr<juce::TextButton> deleteOscButton;
    std::unique_ptr<juce::ToggleButton> syncToggleButton;
    const int buttonsHeight = 25;
    const int oscComponentHeight = 150;

    void loadData();
    void addNewOscillatorComponent(WavetableOscillator* oscillator);
    int getNewComponentHeight();
    void syncWithMain ();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
