#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

//==============================================================================
class SynthPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SynthPluginAudioProcessorEditor (SynthPluginAudioProcessor&);
    ~SynthPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SynthPluginAudioProcessor& audioProcessor;
    
    // UI Components
    juce::GroupComponent synthGroup, arpGroup, delayGroup, reverbGroup, signalGroup, masterGroup;
    
    // Signal generator controls (removed waveform - uses synth waveform)
    juce::ToggleButton signalOnButton;
    juce::Slider signalFreqSlider, signalAmpSlider;
    juce::Label signalOnLabel, signalFreqLabel, signalAmpLabel;
    
    // Synth controls
    juce::ComboBox waveformCombo;
    juce::Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    juce::Label waveformLabel, attackLabel, decayLabel, sustainLabel, releaseLabel;
    
    // Arpeggiator controls
    juce::ToggleButton arpEnabledButton;
    juce::Slider arpRateSlider;
    juce::ComboBox arpPatternCombo;
    juce::Label arpEnabledLabel, arpRateLabel, arpPatternLabel;
    
    // Delay controls
    juce::Slider delayTimeSlider, delayFeedbackSlider, delayMixSlider;
    juce::Label delayTimeLabel, delayFeedbackLabel, delayMixLabel;
    
    // Reverb controls
    juce::Slider reverbRoomSlider, reverbDampingSlider, reverbMixSlider;
    juce::Label reverbRoomLabel, reverbDampingLabel, reverbMixLabel;
    
    // Master controls
    juce::Slider masterVolumeSlider;
    juce::Label masterVolumeLabel;
    
    // Test tone controls
    juce::ToggleButton testToneButton;
    juce::Label testToneLabel;
    
    // Attachments (removed signal waveform - uses synth waveform)
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> signalOnAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> signalFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> signalAmpAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveformAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> arpEnabledAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> arpRateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> arpPatternAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayFeedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayMixAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbRoomAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbDampingAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbMixAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterVolumeAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> testToneAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthPluginAudioProcessorEditor)
};
