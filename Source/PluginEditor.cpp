#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthPluginAudioProcessorEditor::SynthPluginAudioProcessorEditor (SynthPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 600);
    
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
    
    // Setup signal generator group
    signalGroup.setText ("Signal Generator");
    signalGroup.setTextLabelPosition (juce::Justification::centredTop);
    addAndMakeVisible (signalGroup);
    
    // Setup master group
    masterGroup.setText ("Master");
    masterGroup.setTextLabelPosition (juce::Justification::centredTop);
    addAndMakeVisible (masterGroup);
    
    // Setup synth controls
    waveformCombo.addItem ("Sine", 1);
    waveformCombo.addItem ("Sawtooth", 2);
    waveformCombo.addItem ("Square", 3);
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
    
    // Setup test tone button
    testToneButton.setButtonText ("Test Tone");
    testToneButton.setColour (juce::ToggleButton::tickDisabledColourId, juce::Colours::red);
    testToneButton.setColour (juce::ToggleButton::tickColourId, juce::Colours::green);
    addAndMakeVisible (testToneButton);
    testToneLabel.setText ("Test Tone", juce::dontSendNotification);
    testToneLabel.attachToComponent (&testToneButton, false);
    addAndMakeVisible (testToneLabel);
    
    // Setup signal generator controls
    signalOnButton.setButtonText ("PLAY SIGNAL");
    signalOnButton.setColour (juce::ToggleButton::tickDisabledColourId, juce::Colours::red);
    signalOnButton.setColour (juce::ToggleButton::tickColourId, juce::Colours::green);
    signalOnButton.setColour (juce::ToggleButton::textColourId, juce::Colours::white);
    addAndMakeVisible (signalOnButton);
    signalOnLabel.setText ("Signal Generator", juce::dontSendNotification);
    signalOnLabel.attachToComponent (&signalOnButton, false);
    addAndMakeVisible (signalOnLabel);
    
    signalFreqSlider.setSliderStyle (juce::Slider::Rotary);
    signalFreqSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (signalFreqSlider);
    signalFreqLabel.setText ("Frequency", juce::dontSendNotification);
    signalFreqLabel.attachToComponent (&signalFreqSlider, false);
    addAndMakeVisible (signalFreqLabel);
    
    signalAmpSlider.setSliderStyle (juce::Slider::Rotary);
    signalAmpSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (signalAmpSlider);
    signalAmpLabel.setText ("Amplitude", juce::dontSendNotification);
    signalAmpLabel.attachToComponent (&signalAmpSlider, false);
    addAndMakeVisible (signalAmpLabel);
    
    // Note: Signal generator now uses synthesizer waveform instead of separate control
    
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
    
    testToneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::TEST_TONE_ID, testToneButton);
    
    // Signal generator attachments (removed waveform - uses synth waveform)
    signalOnAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::SIGNAL_ON_ID, signalOnButton);
    signalFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::SIGNAL_FREQ_ID, signalFreqSlider);
    signalAmpAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, SynthPluginAudioProcessor::SIGNAL_AMP_ID, signalAmpSlider);
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
    auto bounds = getLocalBounds().reduced(10);
    auto margin = 10;
    
    // Create a 3x2 grid layout
    const int sectionWidth = bounds.getWidth() / 3;
    const int sectionHeight = bounds.getHeight() / 2;
    
    // Define all section bounds
    auto signalBounds = juce::Rectangle<int>(bounds.getX(), bounds.getY(), sectionWidth - 5, sectionHeight - 5);
    auto synthBounds = juce::Rectangle<int>(bounds.getX() + sectionWidth, bounds.getY(), sectionWidth - 5, sectionHeight - 5);
    auto arpBounds = juce::Rectangle<int>(bounds.getX() + sectionWidth * 2, bounds.getY(), sectionWidth - 5, sectionHeight - 5);
    
    auto delayBounds = juce::Rectangle<int>(bounds.getX(), bounds.getY() + sectionHeight, sectionWidth - 5, sectionHeight - 5);
    auto reverbBounds = juce::Rectangle<int>(bounds.getX() + sectionWidth, bounds.getY() + sectionHeight, sectionWidth - 5, sectionHeight - 5);
    auto masterBounds = juce::Rectangle<int>(bounds.getX() + sectionWidth * 2, bounds.getY() + sectionHeight, sectionWidth - 5, sectionHeight - 5);
    
    // Signal Generator section
    signalGroup.setBounds(signalBounds);
    auto signalControls = signalBounds.reduced(margin);
    
    signalOnButton.setBounds(signalControls.removeFromTop(40)); // Make button taller
    signalControls.removeFromTop(10);
    
    auto signalRow1 = signalControls.removeFromTop(80);
    signalFreqSlider.setBounds(signalRow1.removeFromLeft(80));
    signalRow1.removeFromLeft(10);
    signalAmpSlider.setBounds(signalRow1.removeFromLeft(80));
    
    // Note: Waveform is now controlled by the synthesizer waveform setting
    
    // Synth section
    synthGroup.setBounds(synthBounds);
    auto synthControls = synthBounds.reduced(margin);
    waveformCombo.setBounds(synthControls.removeFromTop(25));
    synthControls.removeFromTop(10);
    
    auto synthRow = synthControls.removeFromTop(80);
    auto synthControlWidth = synthRow.getWidth() / 4;
    attackSlider.setBounds(synthRow.removeFromLeft(synthControlWidth).reduced(5));
    decaySlider.setBounds(synthRow.removeFromLeft(synthControlWidth).reduced(5));
    sustainSlider.setBounds(synthRow.removeFromLeft(synthControlWidth).reduced(5));
    releaseSlider.setBounds(synthRow.reduced(5));
    
    // Arpeggiator section
    arpGroup.setBounds(arpBounds);
    auto arpControls = arpBounds.reduced(margin);
    arpEnabledButton.setBounds(arpControls.removeFromTop(35));
    arpControls.removeFromTop(10);
    
    auto arpRow = arpControls.removeFromTop(70);
    arpRateSlider.setBounds(arpRow.removeFromLeft(arpRow.getWidth() / 2).reduced(5));
    
    arpControls.removeFromTop(10);
    arpPatternCombo.setBounds(arpControls.removeFromTop(25));
    
    // Delay section
    delayGroup.setBounds(delayBounds);
    auto delayControls = delayBounds.reduced(margin);
    delayControls.removeFromTop(10); // Space for labels
    auto delayRow = delayControls.removeFromTop(90);
    auto delayControlWidth = delayRow.getWidth() / 3;
    delayTimeSlider.setBounds(delayRow.removeFromLeft(delayControlWidth).reduced(8));
    delayFeedbackSlider.setBounds(delayRow.removeFromLeft(delayControlWidth).reduced(8));
    delayMixSlider.setBounds(delayRow.reduced(8));
    
    // Reverb section
    reverbGroup.setBounds(reverbBounds);
    auto reverbControls = reverbBounds.reduced(margin);
    reverbControls.removeFromTop(10); // Space for labels
    auto reverbRow = reverbControls.removeFromTop(90);
    auto reverbControlWidth = reverbRow.getWidth() / 3;
    reverbRoomSlider.setBounds(reverbRow.removeFromLeft(reverbControlWidth).reduced(8));
    reverbDampingSlider.setBounds(reverbRow.removeFromLeft(reverbControlWidth).reduced(8));
    reverbMixSlider.setBounds(reverbRow.reduced(8));
    
    // Master controls section
    masterGroup.setBounds(masterBounds);
    auto masterControls = masterBounds.reduced(margin);
    masterControls.removeFromTop(10); // Space for label
    masterVolumeSlider.setBounds(masterControls.removeFromTop(100));
    masterControls.removeFromTop(10);
    testToneButton.setBounds(masterControls.removeFromTop(35));
}
