#include "SynthVoice.h"

//==============================================================================
SynthVoice::SynthVoice()
{
    adsrParams.attack = 0.1f;
    adsrParams.decay = 0.3f;
    adsrParams.sustain = 0.7f;
    adsrParams.release = 0.5f;
    adsr.setParameters (adsrParams);
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity,
                           juce::SynthesiserSound* sound,
                           int currentPitchWheelPosition)
{
    frequency = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    phase = 0.0;
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                                 int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;
    
    adsr.setSampleRate (currentSampleRate);
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        auto currentSample = getNextSample() * adsr.getNextSample();
        
        for (int channel = outputBuffer.getNumChannels(); --channel >= 0;)
            outputBuffer.addSample (channel, startSample + sample, currentSample);
        
        if (!adsr.isActive())
        {
            clearCurrentNote();
            break;
        }
    }
}

void SynthVoice::updateParameters (float attack, float decay, float sustain, float release, int waveformType)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    adsr.setParameters (adsrParams);
    
    waveform = waveformType;
}

double SynthVoice::getNextSample()
{
    auto sample = 0.0;
    auto phaseIncrement = frequency / currentSampleRate;
    
    switch (waveform)
    {
        case 0: // Sine wave
            sample = std::sin (phase * 2.0 * juce::MathConstants<double>::pi);
            break;
            
        case 1: // Sawtooth wave
            sample = (2.0 * phase) - 1.0;
            break;
            
        default:
            sample = std::sin (phase * 2.0 * juce::MathConstants<double>::pi);
            break;
    }
    
    phase += phaseIncrement;
    if (phase >= 1.0)
        phase -= 1.0;
    
    return sample * 0.3; // Scale down the volume
}
