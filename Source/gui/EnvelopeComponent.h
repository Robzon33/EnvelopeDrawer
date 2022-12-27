/*
  ==============================================================================

    EnvelopeComponent.h
    Created: 27 Dec 2022 6:31:06pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../synthesiser/Envelope.h"

//==============================================================================
/*
*/
class EnvelopeComponent  : public juce::Component
{
public:
    EnvelopeComponent(Envelope& e);
    ~EnvelopeComponent() override;

    void paint (juce::Graphics&) override;
    void mouseDown(const juce::MouseEvent& event) override;
private:
    Envelope& envelope;
    const int pointDiameterInPixels = 4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeComponent)
};
