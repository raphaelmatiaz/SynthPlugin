#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthPluginAudioProcessorEditor::SynthPluginAudioProcessorEditor (SynthPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 400);
    
    // Setup group components
    synthGroup.setText ("Synthesiser");
    synthGroup.setTextLabelPosition (juce::Justification::centredTop);
    addAndMakeVisible (synthGroup);
    
    arpGroup.setText ("Arpeggiator");
    arpGroup.setTextLabelPosition (juce::Justification::centredTop);
    addAndMakeVisible (arpGroup);
    
    delayGroup.setText ("Delay");
    delayGroup.setTextLabelPosition (juce::Justification::centredTop);
    addAndMakeVisible (delayGroup);
    
    reverbGroup.setText ("Reverb");
    reverbGroup.setTextLabelPosition (juce::Justification::centredTop);
    addAndMakeVisible (reverbGroup);
    
    // Setup synth controls
    waveformCombo.addItem ("Sine", 1);
    waveformCombo.addItem ("Sawtooth", 2);
    addAndMakeVisible (waveformCombo);
    waveformLabel.setText ("Waveform", juce::dontSendNotification);
    waveformLabel.attachToComponent (&waveformCombo, false);
    addAndMakeVisible (waveformLabel);
    
    attackSlider.setSliderStyle (juce::Slider::Rotary);
    attackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (attackSlider);
    attackLabel.setText ("Attack", juce::dontSendNotification);
    attackLabel.attachToComponent (&attackSlider, false);
    addAndMakeVisible (attackLabel);
    
    decaySlider.setSliderStyle (juce::Slider::Rotary);
    decaySlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (decaySlider);
    decayLabel.setText ("Decay", juce::dontSendNotification);
    decayLabel.attachToComponent (&decaySlider, false);
    addAndMakeVisible (decayLabel);
    
    sustainSlider.setSliderStyle (juce::Slider::Rotary);
    sustainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (sustainSlider);
    sustainLabel.setText ("Sustain", juce::dontSendNotification);
    sustainLabel.attachToComponent (&sustainSlider, false);
    addAndMakeVisible (sustainLabel);
    
    releaseSlider.setSliderStyle (juce::Slider::Rotary);
    releaseSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (releaseSlider);
    releaseLabel.setText ("Release", juce::dontSendNotification);
    releaseLabel.attachToComponent (&releaseSlider, false);
    addAndMakeVisible (releaseLabel);
    
    // Setup arpeggiator controls
    addAndMakeVisible (arpEnabledButton);
    arpEnabledLabel.setText ("Enabled", juce::dontSendNotification);
    arpEnabledLabel.attachToComponent (&arpEnabledButton, false);
    addAndMakeVisible (arpEnabledLabel);
    
    arpRateSlider.setSliderStyle (juce::Slider::Rotary);
    arpRateSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (arpRateSlider);
    arpRateLabel.setText ("Rate", juce::dontSendNotification);
    arpRateLabel.attachToComponent (&arpRateSlider, false);
    addAndMakeVisible (arpRateLabel);
    
    arpPatternCombo.addItem ("Up", 1);
    arpPatternCombo.addItem ("Down", 2);
    arpPatternCombo.addItem ("Up-Down", 3);
    arpPatternCombo.addItem ("Random", 4);
    addAndMakeVisible (arpPatternCombo);
    arpPatternLabel.setText ("Pattern", juce::dontSendNotification);
    arpPatternLabel.attachToComponent (&arpPatternCombo, false);
    addAndMakeVisible (arpPatternLabel);
    
    // Setup delay controls
    delayTimeSlider.setSliderStyle (juce::Slider::Rotary);
    delayTimeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (delayTimeSlider);
    delayTimeLabel.setText ("Time", juce::dontSendNotification);
    delayTimeLabel.attachToComponent (&delayTimeSlider, false);
    addAndMakeVisible (delayTimeLabel);
    
    delayFeedbackSlider.setSliderStyle (juce::Slider::Rotary);
    delayFeedbackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (delayFeedbackSlider);
    delayFeedbackLabel.setText ("Feedback", juce::dontSendNotification);
    delayFeedbackLabel.attachToComponent (&delayFeedbackSlider, false);
    addAndMakeVisible (delayFeedbackLabel);
    
    delayMixSlider.setSliderStyle (juce::Slider::Rotary);
    delayMixSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (delayMixSlider);
    delayMixLabel.setText ("Mix", juce::dontSendNotification);
    delayMixLabel.attachToComponent (&delayMixSlider, false);
    addAndMakeVisible (delayMixLabel);
    
    // Setup reverb controls
    reverbRoomSlider.setSliderStyle (juce::Slider::Rotary);
    reverbRoomSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (reverbRoomSlider);
    reverbRoomLabel.setText ("Room", juce::dontSendNotification);
    reverbRoomLabel.attachToComponent (&reverbRoomSlider, false);
    addAndMakeVisible (reverbRoomLabel);
    
    reverbDampingSlider.setSliderStyle (juce::Slider::Rotary);
    reverbDampingSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (reverbDampingSlider);
    reverbDampingLabel.setText ("Damping", juce::dontSendNotification);
    reverbDampingLabel.attachToComponent (&reverbDampingSlider, false);
    addAndMakeVisible (reverbDampingLabel);
    
    reverbMixSlider.setSliderStyle (juce::Slider::Rotary);
    reverbMixSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (reverbMixSlider);
    reverbMixLabel.setText ("Mix", juce::dontSendNotification);
    reverbMixLabel.attachToComponent (&reverbMixSlider, false);
    addAndMakeVisible (reverbMixLabel);
    
    // Setup master volume
    masterVolumeSlider.setSliderStyle (juce::Slider::LinearVertical);
    masterVolumeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (masterVolumeSlider);
    masterVolumeLabel.setText ("Master", juce::dontSendNotification);
    masterVolumeLabel.attachToComponent (&masterVolumeSlider, false);
    addAndMakeVisible (masterVolumeLabel);
    
    // Create parameter attachments
    waveformAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::WAVEFORM_ID, waveformCombo);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::ATTACK_ID, attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::DECAY_ID, decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::SUSTAIN_ID, sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::RELEASE_ID, releaseSlider);
    
    arpEnabledAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::ARP_ENABLED_ID, arpEnabledButton);
    arpRateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::ARP_RATE_ID, arpRateSlider);
    arpPatternAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::ARP_PATTERN_ID, arpPatternCombo);
    
    delayTimeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::DELAY_TIME_ID, delayTimeSlider);
    delayFeedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::DELAY_FEEDBACK_ID, delayFeedbackSlider);
    delayMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::DELAY_MIX_ID, delayMixSlider);
    
    reverbRoomAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::REVERB_ROOM_ID, reverbRoomSlider);
    reverbDampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::REVERB_DAMPING_ID, reverbDampingSlider);
    reverbMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::REVERB_MIX_ID, reverbMixSlider);
    
    masterVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::MASTER_VOLUME_ID, masterVolumeSlider);
}

SynthPluginAudioProcessorEditor::~SynthPluginAudioProcessorEditor()
{
}

//==============================================================================
void SynthPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SynthPluginAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    auto margin = 10;
    
    // Layout sections
    auto synthBounds = bounds.removeFromTop (140).reduced (margin);
    auto arpBounds = bounds.removeFromTop (140).reduced (margin);
    auto effectsBounds = bounds.reduced (margin);
    auto delayBounds = effectsBounds.removeFromLeft (effectsBounds.getWidth() / 2);
    auto reverbBounds = effectsBounds;
    
    // Master volume on the right
    auto masterBounds = bounds.removeFromRight (80).reduced (margin);
    masterVolumeSlider.setBounds (masterBounds);
    
    // Synth section
    synthGroup.setBounds (synthBounds);
    auto synthControls = synthBounds.reduced (margin);
    auto controlWidth = synthControls.getWidth() / 5;
    
    waveformCombo.setBounds (synthControls.removeFromLeft (controlWidth).reduced (5));
    attackSlider.setBounds (synthControls.removeFromLeft (controlWidth).reduced (5));
    decaySlider.setBounds (synthControls.removeFromLeft (controlWidth).reduced (5));
    sustainSlider.setBounds (synthControls.removeFromLeft (controlWidth).reduced (5));
    releaseSlider.setBounds (synthControls.reduced (5));
    
    // Arpeggiator section
    arpGroup.setBounds (arpBounds);
    auto arpControls = arpBounds.reduced (margin);
    auto arpControlWidth = arpControls.getWidth() / 3;
    
    arpEnabledButton.setBounds (arpControls.removeFromLeft (arpControlWidth).reduced (5));
    arpRateSlider.setBounds (arpControls.removeFromLeft (arpControlWidth).reduced (5));
    arpPatternCombo.setBounds (arpControls.reduced (5));
    
    // Delay section
    delayGroup.setBounds (delayBounds);
    auto delayControls = delayBounds.reduced (margin);
    auto delayControlWidth = delayControls.getWidth() / 3;
    
    delayTimeSlider.setBounds (delayControls.removeFromLeft (delayControlWidth).reduced (5));
    delayFeedbackSlider.setBounds (delayControls.removeFromLeft (delayControlWidth).reduced (5));
    delayMixSlider.setBounds (delayControls.reduced (5));
    
    // Reverb section
    reverbGroup.setBounds (reverbBounds);
    auto reverbControls = reverbBounds.reduced (margin);
    auto reverbControlWidth = reverbControls.getWidth() / 3;
    
    reverbRoomSlider.setBounds (reverbControls.removeFromLeft (reverbControlWidth).reduced (5));
    reverbDampingSlider.setBounds (reverbControls.removeFromLeft (reverbControlWidth).reduced (5));
    reverbMixSlider.setBounds (reverbControls.reduced (5));
}
