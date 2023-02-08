/*
  ==============================================================================

    EnvelopeComponent.cpp
    Created: 27 Dec 2022 6:31:06pm
    Author:  Toko

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeComponent.h"

//==============================================================================
EnvelopeComponent::EnvelopeComponent(Envelope& e)
    : envelope(e)
{
    startTimer (50);
}

EnvelopeComponent::~EnvelopeComponent()
{
}

void EnvelopeComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds (), 1);

    for (auto i = 1; i < getWidth () / 50; ++i)
        g.drawVerticalLine (i * 100, 0, getHeight ());

    g.setColour (juce::Colours::green);
    int prevX = -1;
    int prevY = -1;
    for (auto* point : envelope.getPointVector ())
    {
        if (prevX >= 0 && prevY >= 0)
        {
            g.drawLine (prevX, prevY, point->getX (), getHeight () - point->getY (), 1);
        }
        g.fillRoundedRectangle (point->getX () - (pointDiameterInPixels / 2),
                                (getHeight () - point->getY ()) - (pointDiameterInPixels / 2),
                                pointDiameterInPixels,
                                pointDiameterInPixels,
                                1.5f);
        prevX = point->getX ();
        prevY = getHeight () - point->getY ();
    }

    juce::Line<float> line (envelope.getSustainPos (), 0, envelope.getSustainPos (), getHeight ());
    g.drawLine (line);

    g.setColour (juce::Colours::black.withAlpha (0.2f));
    g.fillRect (envelope.getDuration () * 50, 
                0, 
                getWidth () - (envelope.getDuration () * 50), 
                getHeight ());

    g.setColour (juce::Colours::red);
    g.drawVerticalLine (envelope.getCurrentPosInPix (), 0, getHeight ());
}

void EnvelopeComponent::mouseDown(const juce::MouseEvent& event)
{
	if (event.mods.isLeftButtonDown ())
	{
		int index = envelope.getIndexOfPoint ((int) event.getMouseDownX (),
											  getHeight() - (int) event.getMouseDownY ());

        if (index == -1)
        {
            envelope.addPoint ((int) event.getMouseDownX (),
                               getHeight() - (int) event.getMouseDownY ());
        }
        else
        {
            envelope.deletePoint (index);
        }
    }

    repaint ();
}

void EnvelopeComponent::timerCallback ()
{
    repaint ();
}
