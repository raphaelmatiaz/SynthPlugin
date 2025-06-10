#pragma once

#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>

//==============================================================================
class Arpeggiator
{
public:
    enum Pattern
    {
        Up = 0,
        Down,
        UpDown,
        Random
    };
    
    Arpeggiator();
    
    void prepare (double sampleRate);
    void processBlock (juce::MidiBuffer& midiBuffer, int numSamples);
    
    void setEnabled (bool enabled) { isEnabled = enabled; }
    void setRate (float rateHz) { rate = rateHz; }
    void setPattern (int patternIndex) { pattern = static_cast<Pattern>(patternIndex); }
    
    void noteOn (int noteNumber, float velocity);
    void noteOff (int noteNumber);
    void allNotesOff();
    
private:
    struct NoteInfo
    {
        int noteNumber;
        float velocity;
    };
    
    bool isEnabled = false;
    float rate = 8.0f; // Hz
    Pattern pattern = Up;
    
    std::vector<NoteInfo> heldNotes;
    int currentNoteIndex = 0;
    int direction = 1; // 1 for up, -1 for down
    
    double sampleRate = 44100.0;
    double samplesPerBeat = 0.0;
    double sampleCounter = 0.0;
    
    bool lastNoteState = false;
    int lastPlayedNote = -1;
    
    void updateTiming();
    int getNextNote();
};
