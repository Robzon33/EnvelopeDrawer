/*
  ==============================================================================

	Envelope.cpp
	Created: 27 Dec 2022 5:30:51pm
	Author:  Toko

  ==============================================================================
*/

#include "Envelope.h"


Envelope::Envelope (double sampleRate)
{
	this->duration = 10;
	this->sampleRate = sampleRate;
	this->sustainPos = 150;

	pointVector.insert (0, new juce::Point<int> (0, 0));
	pointVector.insert (2, new juce::Point<int> (500, 0));
}

Envelope::~Envelope ()
{
}

void Envelope::setSampleRate (double newSampleRate) noexcept
{
	jassert (newSampleRate > 0.0);
	sampleRate = newSampleRate;
}

float Envelope::getNextSample () noexcept
{
	switch (state)
	{
		case State::idle:
		{
			break;
		}
		case State::running:
		{
			currentPosInSec += (1 / sampleRate);
			currentPosInPix = currentPosInSec * 50;
			if (currentPosInPix >= sustainPos)
			{
				state = State::sustain;
			}
			else
			{
				if (currentPosInPix == 10)
					int a = 5;
				envelopeVal = getEnvelopeValue (currentPosInPix);
			}
			break;
		}
		case State::sustain:
		{
			envelopeVal = getEnvelopeValue (sustainPos);
			break;
		}
		case State::release:
		{
			currentPosInSec += (1 / sampleRate);
			if (currentPosInSec >= duration)
			{
				reset ();
			}
			else
			{
				currentPosInPix = currentPosInSec * 50;
				envelopeVal = getEnvelopeValue (currentPosInPix);
			}
			break;
		}
	}

	jassert (envelopeVal >= 0.0f && envelopeVal <= 1.0f);

	return envelopeVal;
}

void Envelope::setSustainPos (int newSustainPos)
{
	sustainPos = newSustainPos;
}

int Envelope::getSustainPos ()
{
	return sustainPos;
}

double Envelope::getSustainPosInSec ()
{
	return (double) sustainPos / 50;
}

void Envelope::setDuration (double newDuration)
{
	if (newDuration > 0 && newDuration <= 10)
		duration = newDuration;
}

double Envelope::getDuration ()
{
	return duration;
}

void Envelope::addPoint (int x, int y)
{
	if (pointVector.size () < maxNumberOfPoints)
	{
		for (int i = 0; i < pointVector.size (); ++i)
		{
			if (pointVector[i]->getX () > x)
			{
				pointVector.insert (i, new juce::Point<int> (x, y));
				break;
			}
		}
	}
}

void Envelope::deletePoint (int index)
{
	if (index > 0 && index < pointVector.size () - 1)
	{
		pointVector.remove (index);
	}
}

juce::OwnedArray<juce::Point<int>>& Envelope::getPointVector ()
{
	return pointVector;
}

int Envelope::getIndexOfPoint (int x, int y)
{
	for (int i = 0; i < this->pointVector.size (); i++)
	{
		if (abs (this->pointVector[i]->getX () - x) < deviation &&
			abs (this->pointVector[i]->getY () - y) < deviation)
		{
			return i;
		}
	}
	return -1;
}

int Envelope::getCurrentPosInPix ()
{
	return currentPosInPix;
}

void Envelope::reset () noexcept
{
	envelopeVal = 0.0f;
	state = State::idle;
	currentPosInPix = 0;
	currentPosInSec = 0.0f;
}

void Envelope::noteOn () noexcept
{
	if (currentPosInPix < sustainPos)
	{
		state = State::running;
	}
	else
	{
		state = State::sustain;
	}
}

void Envelope::noteOff () noexcept
{
	if (state != State::idle)
	{
		state = State::release;
	}
}

float Envelope::getEnvelopeValue (int x)
{
	auto envelopeValue = -1.0f;

	for (auto i = 1;i < pointVector.size (); ++i)
	{
		if (x < pointVector.getUnchecked (i)->getX ())
		{
			float diffY = (float) pointVector.getUnchecked (i)->getY () 
						  - (float) pointVector.getUnchecked (i - 1)->getY ();
			float diffX = (float) pointVector.getUnchecked(i)->getX () 
						  - (float) pointVector.getUnchecked(i - 1)->getX ();
			float m = diffY / diffX;
			float n = pointVector.getUnchecked (i)->getY () 
					  - (m * pointVector.getUnchecked (i)->getX ());

			envelopeValue = (m * x) + n;
			break;
		}
		else if (x == pointVector.getUnchecked (i)->getX ())
		{
			envelopeValue = pointVector.getUnchecked (i)->getY ();
			break;
		}
	}

	// convert envelope value from pixel to float value between 0 and 1
	envelopeValue /= 100.0f;

	//jassert (envelopeValue == -1.0f || envelopeValue > 1.0f);
	jassert (envelopeValue >= 0.0f && envelopeValue <= 1.0f);
	
	return envelopeValue;
}
