#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

//==============================================================================
class ReverbEffect
{
public:
    ReverbEffect();
    
    void prepare (double sampleRate, int maxBlockSize);
    void reset();
    
    void processBlock (juce::AudioBuffer<float>& buffer);
    
    void setRoomSize (float roomSize);
    void setDamping (float damping);
    void setMix (float mix);
    
private:
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams;
    
    float mix = 0.3f;
    
    juce::AudioBuffer<float> dryBuffer;
};
