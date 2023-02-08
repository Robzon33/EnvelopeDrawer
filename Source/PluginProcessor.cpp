/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EnvelopeDrawerAudioProcessor::EnvelopeDrawerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    midiKeyboardState.reset(new juce::MidiKeyboardState());
    mySynth.reset(new Synth());
}

EnvelopeDrawerAudioProcessor::~EnvelopeDrawerAudioProcessor()
{
}

//==============================================================================
const juce::String EnvelopeDrawerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EnvelopeDrawerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EnvelopeDrawerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EnvelopeDrawerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EnvelopeDrawerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EnvelopeDrawerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EnvelopeDrawerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EnvelopeDrawerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EnvelopeDrawerAudioProcessor::getProgramName (int index)
{
    return {};
}

void EnvelopeDrawerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EnvelopeDrawerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mySynth->setCurrentPlaybackSampleRate(sampleRate);
    midiKeyboardState->reset();

    for (int i = 0; i < mySynth->getNumVoices(); ++i)
    {
        if (dynamic_cast<SynthVoice*>(mySynth->getVoice(i)) != nullptr)
        {
            dynamic_cast<SynthVoice*>(mySynth->getVoice(i))->setSampleRate(this->getSampleRate());
        }
    }
}

void EnvelopeDrawerAudioProcessor::releaseResources()
{
    midiKeyboardState->reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EnvelopeDrawerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EnvelopeDrawerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    midiKeyboardState->processNextMidiBuffer(midiMessages, 0, numSamples, true);
    mySynth->renderNextBlock(buffer, midiMessages, 0, numSamples);
}

//==============================================================================
bool EnvelopeDrawerAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* EnvelopeDrawerAudioProcessor::createEditor()
{
    return new EnvelopeDrawerAudioProcessorEditor (*this);
}

//==============================================================================
void EnvelopeDrawerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EnvelopeDrawerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
juce::MidiKeyboardState* EnvelopeDrawerAudioProcessor::getMidiKeyboardState()
{
    return midiKeyboardState.get();
}

Synth* EnvelopeDrawerAudioProcessor::getSynth()
{
    return mySynth.get();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EnvelopeDrawerAudioProcessor();
}
