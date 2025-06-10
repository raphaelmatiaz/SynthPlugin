# SynthPlugin - JUCE VST3 Instrument

A modern VST3 instrument plugin built with JUCE framework, featuring a synthesizer with arpeggiator and built-in effects.

## Features

### 🎹 Synthesizer
- **Waveforms**: Sine and Sawtooth oscillators
- **ADSR Envelope**: Full Attack, Decay, Sustain, Release controls
- **Polyphony**: 8-voice polyphonic playback
- **Real-time Parameter Control**: All parameters are automatable

### 🎵 Arpeggiator
- **Patterns**: Up, Down, Up-Down, Random
- **Rate Control**: Adjustable tempo from 1-16 Hz
- **Enable/Disable**: Toggle arpeggiator on/off
- **Smart Note Management**: Automatic note sorting and management

### 🔊 Effects
- **Delay**: 
  - Time: 10ms - 1000ms
  - Feedback: 0-95%
  - Wet/Dry Mix control
- **Reverb**:
  - Room Size control
  - Damping control
  - Wet/Dry Mix control

### 🎛️ User Interface
- **Organized Layout**: Four grouped sections for easy navigation
- **Real-time Controls**: Responsive knobs and sliders
- **Parameter Automation**: Full DAW integration
- **Master Volume**: Global output control

## Requirements

### Build Dependencies
- **JUCE Framework** (included as submodule)
- **CMake** 3.15 or higher
- **C++17** compatible compiler
- **Audio Development Libraries**:
  - ALSA (Linux)
  - Core Audio (macOS)
  - ASIO/DirectSound (Windows)

### Runtime Requirements
- **DAW** supporting VST3 plugins (REAPER, Cupertino Logic Pro, Ableton Live, etc.)
- **Operating System**: Linux, macOS, or Windows

## Building

### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt update
sudo apt install -y cmake pkg-config libasound2-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libfreetype6-dev libwebkit2gtk-4.0-dev libglu1-mesa-dev

# Clone repository with JUCE submodule
git clone --recursive https://github.com/yourusername/SynthPlugin.git
cd SynthPlugin

# Build
mkdir build && cd build
cmake ..
make -j4
```

### macOS
```bash
# Install Xcode command line tools
xcode-select --install

# Clone and build
git clone --recursive https://github.com/yourusername/SynthPlugin.git
cd SynthPlugin
mkdir build && cd build
cmake ..
make -j4
```

### Windows
```bash
# Using Visual Studio 2019/2022
git clone --recursive https://github.com/yourusername/SynthPlugin.git
cd SynthPlugin
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

## Installation

After building, the plugin will be automatically installed to:
- **Linux**: `~/.vst3/SynthPlugin.vst3`
- **macOS**: `~/Library/Audio/Plug-Ins/VST3/SynthPlugin.vst3`
- **Windows**: `%COMMONPROGRAMFILES%\VST3\SynthPlugin.vst3`

## Usage

1. **Load in DAW**: Open your DAW and scan for new plugins
2. **Create Track**: Add SynthPlugin as a virtual instrument
3. **MIDI Input**: Connect MIDI keyboard or draw MIDI notes
4. **Parameter Control**: Adjust synthesizer, arpeggiator, and effects in real-time

### Parameter Guide

#### Synthesizer
- **Waveform**: Choose between Sine and Sawtooth
- **Attack**: Envelope attack time (0.01-5 seconds)
- **Decay**: Envelope decay time (0.01-5 seconds)
- **Sustain**: Envelope sustain level (0-100%)
- **Release**: Envelope release time (0.01-5 seconds)

#### Arpeggiator
- **Enabled**: Turn arpeggiator on/off
- **Rate**: Arpeggio speed (1-16 Hz)
- **Pattern**: Note sequence pattern

#### Effects
- **Delay Time**: Echo delay time
- **Delay Feedback**: Echo repetition amount
- **Delay Mix**: Dry/wet balance for delay
- **Reverb Room**: Simulated room size
- **Reverb Damping**: High frequency absorption
- **Reverb Mix**: Dry/wet balance for reverb

## Project Structure

```
SynthPlugin/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── .gitignore                  # Git ignore rules
└── Source/
    ├── PluginProcessor.h/cpp   # Main plugin logic
    ├── PluginEditor.h/cpp      # User interface
    ├── SynthVoice.h/cpp        # Synthesizer voice
    ├── Arpeggiator.h/cpp       # Arpeggiator logic
    ├── DelayEffect.h/cpp       # Delay effect
    └── ReverbEffect.h/cpp      # Reverb effect
```

## Technical Details

- **Framework**: JUCE 7.x
- **Plugin Format**: VST3
- **Audio Processing**: 32-bit float, variable sample rates
- **MIDI**: Full MIDI input support
- **Threading**: Real-time safe audio processing
- **Parameters**: Automatable with smooth value changes

## Development

### Code Style
- Modern C++17 features
- JUCE coding conventions
- Modular architecture for easy expansion
- Comprehensive parameter management

### Future Enhancements
- Additional waveforms (triangle, square, noise)
- Filter section with cutoff and resonance
- LFO modulation
- Additional arpeggiator patterns
- Preset management
- Additional effects (chorus, phaser)

## License

This project is open source. Please check the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Support

For support, questions, or feedback:
- Open an issue on GitHub
- Check the JUCE documentation for framework-specific questions

---

Built with ❤️ using the JUCE framework
