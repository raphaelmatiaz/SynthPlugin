#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================
class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};

//==============================================================================
class SynthVoice : public juce::SynthesiserVoice
{
public:
    SynthVoice();
    
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity,
                   juce::SynthesiserSound* sound,
                   int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override {}
    void controllerMoved (int controllerNumber, int newControllerValue) override {}
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                         int startSample, int numSamples) override;
    
    void updateParameters (float attack, float decay, float sustain, float release, int waveformType);
    
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    double currentSampleRate = 44100.0;
    double frequency = 440.0;
    double phase = 0.0;
    int waveform = 0; // 0 = sine, 1 = sawtooth
    
    double getNextSample();
};
