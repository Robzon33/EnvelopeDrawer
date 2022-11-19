/*
  ==============================================================================

    ADSRComponent.h
    Created: 19 Nov 2022 7:48:18pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSRComponent  : public juce::Component
{
public:
    ADSRComponent();
    ~ADSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
