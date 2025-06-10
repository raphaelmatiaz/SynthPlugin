#include "DelayEffect.h"

//==============================================================================
DelayEffect::DelayEffect()
{
}

void DelayEffect::prepare (double sampleRate, int maxBlockSize)
{
    this->sampleRate = sampleRate;
    
    // Initialize delay line with maximum delay time of 2 seconds
    auto maxDelaySamples = static_cast<int> (sampleRate * 2.0);
    delayLine.prepare ({ sampleRate, static_cast<juce::uint32> (maxBlockSize), 2 });
    delayLine.setMaximumDelayInSamples (maxDelaySamples);
    
    updateDelayTime();
}

void DelayEffect::reset()
{
    delayLine.reset();
}

void DelayEffect::processBlock (juce::AudioBuffer<float>& buffer)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            auto inputSample = channelData[sample];
            
            // Get delayed sample
            auto delayedSample = delayLine.popSample (channel, delaySamples);
            
            // Create feedback sample
            auto feedbackSample = inputSample + (delayedSample * feedback);
            
            // Push to delay line
            delayLine.pushSample (channel, feedbackSample);
            
            // Mix dry and wet signals
            channelData[sample] = inputSample * (1.0f - mix) + delayedSample * mix;
        }
    }
}

void DelayEffect::setDelayTime (float delayTimeMs)
{
    this->delayTimeMs = delayTimeMs;
    updateDelayTime();
}

void DelayEffect::setFeedback (float feedback)
{
    this->feedback = juce::jlimit (0.0f, 0.95f, feedback);
}

void DelayEffect::setMix (float mix)
{
    this->mix = juce::jlimit (0.0f, 1.0f, mix);
}

void DelayEffect::updateDelayTime()
{
    delaySamples = static_cast<int> ((delayTimeMs / 1000.0f) * sampleRate);
    delayLine.setDelay (static_cast<float> (delaySamples));
}
