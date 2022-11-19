/*
  ==============================================================================

    KeyboardComponent.cpp
    Created: 19 Nov 2022 7:47:51pm
    Author:  Toko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KeyboardComponent.h"

//==============================================================================
KeyboardComponent::KeyboardComponent(juce::MidiKeyboardState& mks)
    : keyboardComponent(mks, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(keyboardComponent);
}

KeyboardComponent::~KeyboardComponent()
{
}

void KeyboardComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void KeyboardComponent::resized()
{
    keyboardComponent.setBounds(getLocalBounds().reduced(5));
}
