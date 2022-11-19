/*
  ==============================================================================

    KeyboardComponent.h
    Created: 19 Nov 2022 7:47:51pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class KeyboardComponent  : public juce::Component
{
public:
    KeyboardComponent();
    ~KeyboardComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};
