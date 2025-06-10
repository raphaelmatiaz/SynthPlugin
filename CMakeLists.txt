cmake_minimum_required(VERSION 3.15)

project(SynthPlugin VERSION 1.0.0)

# Add JUCE to the project
add_subdirectory(JUCE)

# Create the plugin target
juce_add_plugin(SynthPlugin
    COMPANY_NAME "YourCompany"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Manu
    PLUGIN_CODE SyPl
    FORMATS VST3
    PRODUCT_NAME "SynthPlugin")

# Set source files
target_sources(SynthPlugin
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/SynthVoice.cpp
        Source/Arpeggiator.cpp
        Source/DelayEffect.cpp
        Source/ReverbEffect.cpp)

# Link required JUCE modules
target_link_libraries(SynthPlugin
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors
        juce::juce_core
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

# Set C++ standard
target_compile_features(SynthPlugin PRIVATE cxx_std_17)

# Set preprocessor definitions
target_compile_definitions(SynthPlugin
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)
