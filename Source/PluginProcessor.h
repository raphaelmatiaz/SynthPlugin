#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>
#include "SynthVoice.h"
#include "Arpeggiator.h"
#include "DelayEffect.h"
#include "ReverbEffect.h"

//==============================================================================
class SynthPluginAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    SynthPluginAudioProcessor();
    ~SynthPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    // Parameters
    juce::AudioProcessorValueTreeState parameters;
    
    // Parameter IDs
    static const juce::String WAVEFORM_ID;
    static const juce::String ATTACK_ID;
    static const juce::String DECAY_ID;
    static const juce::String SUSTAIN_ID;
    static const juce::String RELEASE_ID;
    static const juce::String ARP_ENABLED_ID;
    static const juce::String ARP_RATE_ID;
    static const juce::String ARP_PATTERN_ID;
    static const juce::String DELAY_TIME_ID;
    static const juce::String DELAY_FEEDBACK_ID;
    static const juce::String DELAY_MIX_ID;
    static const juce::String REVERB_ROOM_ID;
    static const juce::String REVERB_DAMPING_ID;
    static const juce::String REVERB_MIX_ID;
    static const juce::String MASTER_VOLUME_ID;
    static const juce::String TEST_TONE_ID;
    
    // Signal generator parameter IDs
    static const juce::String SIGNAL_ON_ID;
    static const juce::String SIGNAL_FREQ_ID;
    static const juce::String SIGNAL_AMP_ID;
    static const juce::String SIGNAL_WAVE_ID;

private:
    //==============================================================================
    juce::Synthesiser synthesiser;
    Arpeggiator arpeggiator;
    DelayEffect delay;
    ReverbEffect reverb;
    
    // Signal generator members
    bool isSignalGeneratorOn = false;
    double signalPhase = 0.0;
    double signalFrequency = 440.0;
    double signalAmplitude = 0.5;
    int signalWaveform = 0; // 0 = sine, 1 = sawtooth, 2 = square
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void generateSignal(juce::AudioBuffer<float>& buffer);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthPluginAudioProcessor)
};
