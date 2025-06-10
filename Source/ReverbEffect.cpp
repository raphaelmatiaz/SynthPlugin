#include "ReverbEffect.h"

//==============================================================================
ReverbEffect::ReverbEffect()
{
    reverbParams.roomSize = 0.5f;
    reverbParams.damping = 0.5f;
    reverbParams.wetLevel = 0.3f;
    reverbParams.dryLevel = 0.7f;
    reverbParams.width = 1.0f;
    reverbParams.freezeMode = 0.0f;
    
    reverb.setParameters (reverbParams);
}

void ReverbEffect::prepare (double sampleRate, int maxBlockSize)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (maxBlockSize);
    spec.numChannels = 2;
    
    reverb.prepare (spec);
    
    dryBuffer.setSize (2, maxBlockSize);
}

void ReverbEffect::reset()
{
    reverb.reset();
}

void ReverbEffect::processBlock (juce::AudioBuffer<float>& buffer)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    
    // Ensure we have stereo buffer for reverb processing
    if (numChannels == 1)
    {
        // Duplicate mono to stereo for processing
        buffer.setSize (2, numSamples, true, true, true);
        buffer.copyFrom (1, 0, buffer, 0, 0, numSamples);
    }
    
    // Store dry signal
    dryBuffer.setSize (numChannels, numSamples, false, false, true);
    dryBuffer.makeCopyOf (buffer, true);
    
    // Create audio block for DSP processing
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    
    // Process reverb
    reverb.process (context);
    
    // Mix dry and wet signals
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* wetData = buffer.getWritePointer (channel);
        auto* dryData = dryBuffer.getReadPointer (channel);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            wetData[sample] = dryData[sample] * (1.0f - mix) + wetData[sample] * mix;
        }
    }
}

void ReverbEffect::setRoomSize (float roomSize)
{
    reverbParams.roomSize = juce::jlimit (0.0f, 1.0f, roomSize);
    reverb.setParameters (reverbParams);
}

void ReverbEffect::setDamping (float damping)
{
    reverbParams.damping = juce::jlimit (0.0f, 1.0f, damping);
    reverb.setParameters (reverbParams);
}

void ReverbEffect::setMix (float mix)
{
    this->mix = juce::jlimit (0.0f, 1.0f, mix);
}
