#include "Arpeggiator.h"

//==============================================================================
Arpeggiator::Arpeggiator()
{
    updateTiming();
}

void Arpeggiator::prepare (double sampleRate)
{
    this->sampleRate = sampleRate;
    updateTiming();
}

void Arpeggiator::processBlock (juce::MidiBuffer& midiBuffer, int numSamples)
{
    if (!isEnabled || heldNotes.empty())
        return;
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        sampleCounter += 1.0;
        
        if (sampleCounter >= samplesPerBeat)
        {
            sampleCounter -= samplesPerBeat;
            
            // Turn off previous note
            if (lastPlayedNote >= 0)
            {
                auto noteOffMessage = juce::MidiMessage::noteOff (1, lastPlayedNote, 0.0f);
                midiBuffer.addEvent (noteOffMessage, sample);
            }
            
            // Get next note and turn it on
            int noteToPlay = getNextNote();
            if (noteToPlay >= 0)
            {
                auto noteOnMessage = juce::MidiMessage::noteOn (1, noteToPlay, 0.8f);
                midiBuffer.addEvent (noteOnMessage, sample);
                lastPlayedNote = noteToPlay;
            }
        }
    }
}

void Arpeggiator::noteOn (int noteNumber, float velocity)
{
    // Add note if not already present
    for (const auto& note : heldNotes)
    {
        if (note.noteNumber == noteNumber)
            return;
    }
    
    heldNotes.push_back ({noteNumber, velocity});
    
    // Sort notes by pitch for consistent patterns
    std::sort (heldNotes.begin(), heldNotes.end(),
               [](const NoteInfo& a, const NoteInfo& b) {
                   return a.noteNumber < b.noteNumber;
               });
    
    // Reset arp position when new notes are added
    currentNoteIndex = 0;
    direction = 1;
}

void Arpeggiator::noteOff (int noteNumber)
{
    heldNotes.erase (std::remove_if (heldNotes.begin(), heldNotes.end(),
                                     [noteNumber](const NoteInfo& note) {
                                         return note.noteNumber == noteNumber;
                                     }),
                     heldNotes.end());
    
    // Adjust current index if needed
    if (currentNoteIndex >= static_cast<int> (heldNotes.size()) && !heldNotes.empty())
        currentNoteIndex = static_cast<int> (heldNotes.size()) - 1;
}

void Arpeggiator::allNotesOff()
{
    heldNotes.clear();
    currentNoteIndex = 0;
    lastPlayedNote = -1;
}

void Arpeggiator::updateTiming()
{
    samplesPerBeat = sampleRate / rate;
}

int Arpeggiator::getNextNote()
{
    if (heldNotes.empty())
        return -1;
    
    int noteIndex = 0;
    
    switch (pattern)
    {
        case Up:
            noteIndex = currentNoteIndex;
            currentNoteIndex = (currentNoteIndex + 1) % static_cast<int> (heldNotes.size());
            break;
            
        case Down:
            noteIndex = static_cast<int> (heldNotes.size()) - 1 - currentNoteIndex;
            currentNoteIndex = (currentNoteIndex + 1) % static_cast<int> (heldNotes.size());
            break;
            
        case UpDown:
            noteIndex = currentNoteIndex;
            currentNoteIndex += direction;
            
            if (currentNoteIndex >= static_cast<int> (heldNotes.size()))
            {
                currentNoteIndex = static_cast<int> (heldNotes.size()) - 2;
                direction = -1;
            }
            else if (currentNoteIndex < 0)
            {
                currentNoteIndex = 1;
                direction = 1;
            }
            
            // Handle single note case
            if (heldNotes.size() == 1)
                currentNoteIndex = 0;
            break;
            
        case Random:
            noteIndex = juce::Random::getSystemRandom().nextInt (static_cast<int> (heldNotes.size()));
            break;
    }
    
    return heldNotes[noteIndex].noteNumber;
}
