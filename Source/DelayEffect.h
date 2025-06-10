#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

//==============================================================================
class DelayEffect
{
public:
    DelayEffect();
    
    void prepare (double sampleRate, int maxBlockSize);
    void reset();
    
    void processBlock (juce::AudioBuffer<float>& buffer);
    
    void setDelayTime (float delayTimeMs);
    void setFeedback (float feedback);
    void setMix (float mix);
    
private:
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine;
    
    double sampleRate = 44100.0;
    float delayTimeMs = 250.0f;
    float feedback = 0.3f;
    float mix = 0.3f;
    
    int delaySamples = 0;
    
    void updateDelayTime();
};
