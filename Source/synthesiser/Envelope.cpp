/*
  ==============================================================================

    Envelope.cpp
    Created: 27 Dec 2022 5:30:51pm
    Author:  Toko

  ==============================================================================
*/

#include "Envelope.h"


Envelope::Envelope()
{
    duration = 10;
    sampleRate = 44100;

    pointVector.insert (0, new juce::Point<int> (0, 0));
    pointVector.insert (1, new juce::Point<int> (500, 0));
}

Envelope::~Envelope()
{
}

void Envelope::setSampleRate(double newSampleRate) noexcept
{
    sampleRate = newSampleRate;
}

float Envelope::getNextSample() noexcept
{
    return 1.0f;
}

void Envelope::setDuration(double newDuration)
{
	if (newDuration > 0 && newDuration <= 10)
		duration = newDuration;
}

double Envelope::getDuration()
{
    return duration;
}

void Envelope::addPoint(int x, int y)
{
    if (pointVector.size() < maxNumberOfPoints)
    {
        for (int i = 0; i < pointVector.size(); ++i)
        {
            if (pointVector[i]->getX() > x)
            {
                pointVector.insert(i, new juce::Point<int>(x, y));
                break;
            }
        }
    }
}

void Envelope::deletePoint(int index)
{
    if (index > 0 && index < pointVector.size() - 1)
    {
        pointVector.remove(index);
    }
}

juce::OwnedArray<juce::Point<int>>& Envelope::getPointVector()
{
    return pointVector;
}

int Envelope::getIndexOfPoint(int x, int y)
{
    for (int i = 0; i < this->pointVector.size(); i++)
    {
        if (abs(this->pointVector[i]->getX() - x) < deviation &&
            abs(this->pointVector[i]->getY() - y) < deviation)
        {
            return i;
        }
    }
    return -1;
}