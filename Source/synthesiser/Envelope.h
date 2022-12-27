/*
  ==============================================================================

    Envelope.h
    Created: 27 Dec 2022 5:30:51pm
    Author:  Toko

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Envelope
{
public:
    Envelope();
    ~Envelope();

    void setSampleRate(double newSampleRate) noexcept;
    float getNextSample() noexcept;

    void setDuration(double newDuration);
    double getDuration();
    void addPoint(int x, int y);
    void deletePoint(int index);
    juce::OwnedArray<juce::Point<int>>& getPointVector();
    int getIndexOfPoint(int x, int y);
private:
    enum class State { idle, running };

    State state = State::idle;

    double sampleRate = 0;
    juce::OwnedArray<juce::Point<int>> pointVector;
    double duration = 10;
    const int maxNumberOfPoints = 20;
    const int deviation = 4;
};