#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// Parameter IDs
const juce::String SynthPluginAudioProcessor::WAVEFORM_ID = "waveform";
const juce::String SynthPluginAudioProcessor::ATTACK_ID = "attack";
const juce::String SynthPluginAudioProcessor::DECAY_ID = "decay";
const juce::String SynthPluginAudioProcessor::SUSTAIN_ID = "sustain";
const juce::String SynthPluginAudioProcessor::RELEASE_ID = "release";
const juce::String SynthPluginAudioProcessor::ARP_ENABLED_ID = "arpEnabled";
const juce::String SynthPluginAudioProcessor::ARP_RATE_ID = "arpRate";
const juce::String SynthPluginAudioProcessor::ARP_PATTERN_ID = "arpPattern";
const juce::String SynthPluginAudioProcessor::DELAY_TIME_ID = "delayTime";
const juce::String SynthPluginAudioProcessor::DELAY_FEEDBACK_ID = "delayFeedback";
const juce::String SynthPluginAudioProcessor::DELAY_MIX_ID = "delayMix";
const juce::String SynthPluginAudioProcessor::REVERB_ROOM_ID = "reverbRoom";
const juce::String SynthPluginAudioProcessor::REVERB_DAMPING_ID = "reverbDamping";
const juce::String SynthPluginAudioProcessor::REVERB_MIX_ID = "reverbMix";
const juce::String SynthPluginAudioProcessor::MASTER_VOLUME_ID = "masterVolume";

//==============================================================================
SynthPluginAudioProcessor::SynthPluginAudioProcessor()
    : AudioProcessor (BusesProperties()
                      .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      parameters (*this, nullptr, juce::Identifier ("SynthPlugin"), createParameterLayout())
{
    // Add voices to the synthesiser
    for (int i = 0; i < 8; ++i)
        synthesiser.addVoice (new SynthVoice());
    
    synthesiser.addSound (new SynthSound());
}

SynthPluginAudioProcessor::~SynthPluginAudioProcessor()
{
}

//==============================================================================
const juce::String SynthPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthPluginAudioProcessor::getNumPrograms()
{
    return 1;
}

int SynthPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synthesiser.setCurrentPlaybackSampleRate (sampleRate);
    
    arpeggiator.prepare (sampleRate);
    delay.prepare (sampleRate, samplesPerBlock);
    reverb.prepare (sampleRate, samplesPerBlock);
}

void SynthPluginAudioProcessor::releaseResources()
{
    delay.reset();
    reverb.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}
#endif

void SynthPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Update voice parameters
    auto attack = parameters.getRawParameterValue (ATTACK_ID)->load();
    auto decay = parameters.getRawParameterValue (DECAY_ID)->load();
    auto sustain = parameters.getRawParameterValue (SUSTAIN_ID)->load();
    auto release = parameters.getRawParameterValue (RELEASE_ID)->load();
    auto waveform = static_cast<int> (parameters.getRawParameterValue (WAVEFORM_ID)->load());
    
    for (int i = 0; i < synthesiser.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*> (synthesiser.getVoice (i)))
        {
            voice->updateParameters (attack, decay, sustain, release, waveform);
        }
    }
    
    // Update arpeggiator
    auto arpEnabled = parameters.getRawParameterValue (ARP_ENABLED_ID)->load() > 0.5f;
    auto arpRate = parameters.getRawParameterValue (ARP_RATE_ID)->load();
    auto arpPattern = static_cast<int> (parameters.getRawParameterValue (ARP_PATTERN_ID)->load());
    
    arpeggiator.setEnabled (arpEnabled);
    arpeggiator.setRate (arpRate);
    arpeggiator.setPattern (arpPattern);
    
    // Process MIDI through arpeggiator
    if (arpEnabled)
    {
        // Handle input MIDI for arpeggiator
        for (const auto metadata : midiMessages)
        {
            auto message = metadata.getMessage();
            if (message.isNoteOn())
                arpeggiator.noteOn (message.getNoteNumber(), message.getFloatVelocity());
            else if (message.isNoteOff())
                arpeggiator.noteOff (message.getNoteNumber());
        }
        
        // Clear original MIDI and let arpeggiator generate new MIDI
        midiMessages.clear();
        arpeggiator.processBlock (midiMessages, buffer.getNumSamples());
    }
    
    // Render synthesiser
    synthesiser.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
    
    // Apply effects
    delay.setDelayTime (parameters.getRawParameterValue (DELAY_TIME_ID)->load());
    delay.setFeedback (parameters.getRawParameterValue (DELAY_FEEDBACK_ID)->load());
    delay.setMix (parameters.getRawParameterValue (DELAY_MIX_ID)->load());
    delay.processBlock (buffer);
    
    reverb.setRoomSize (parameters.getRawParameterValue (REVERB_ROOM_ID)->load());
    reverb.setDamping (parameters.getRawParameterValue (REVERB_DAMPING_ID)->load());
    reverb.setMix (parameters.getRawParameterValue (REVERB_MIX_ID)->load());
    reverb.processBlock (buffer);
    
    // Apply master volume
    auto masterVolume = parameters.getRawParameterValue (MASTER_VOLUME_ID)->load();
    buffer.applyGain (masterVolume);
}

//==============================================================================
bool SynthPluginAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* SynthPluginAudioProcessor::createEditor()
{
    return new SynthPluginAudioProcessorEditor (*this);
}

//==============================================================================
void SynthPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void SynthPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SynthPluginAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Synth parameters
    params.push_back (std::make_unique<juce::AudioParameterChoice> (WAVEFORM_ID, "Waveform", 
                      juce::StringArray { "Sine", "Sawtooth" }, 0));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (ATTACK_ID, "Attack", 0.01f, 5.0f, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (DECAY_ID, "Decay", 0.01f, 5.0f, 0.3f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (SUSTAIN_ID, "Sustain", 0.0f, 1.0f, 0.7f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (RELEASE_ID, "Release", 0.01f, 5.0f, 0.5f));
    
    // Arpeggiator parameters
    params.push_back (std::make_unique<juce::AudioParameterBool> (ARP_ENABLED_ID, "Arp Enabled", false));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (ARP_RATE_ID, "Arp Rate", 1.0f, 16.0f, 8.0f));
    params.push_back (std::make_unique<juce::AudioParameterChoice> (ARP_PATTERN_ID, "Arp Pattern",
                      juce::StringArray { "Up", "Down", "Up-Down", "Random" }, 0));
    
    // Delay parameters
    params.push_back (std::make_unique<juce::AudioParameterFloat> (DELAY_TIME_ID, "Delay Time", 10.0f, 1000.0f, 250.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (DELAY_FEEDBACK_ID, "Delay Feedback", 0.0f, 0.95f, 0.3f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (DELAY_MIX_ID, "Delay Mix", 0.0f, 1.0f, 0.3f));
    
    // Reverb parameters
    params.push_back (std::make_unique<juce::AudioParameterFloat> (REVERB_ROOM_ID, "Reverb Room", 0.0f, 1.0f, 0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (REVERB_DAMPING_ID, "Reverb Damping", 0.0f, 1.0f, 0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (REVERB_MIX_ID, "Reverb Mix", 0.0f, 1.0f, 0.3f));
    
    // Master parameters
    params.push_back (std::make_unique<juce::AudioParameterFloat> (MASTER_VOLUME_ID, "Master Volume", 0.0f, 1.0f, 0.8f));
    
    return { params.begin(), params.end() };
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthPluginAudioProcessor();
}
