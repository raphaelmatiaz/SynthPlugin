#!/bin/bash

# Build script to cross-compile SynthPlugin for Windows from WSL

echo "Building SynthPlugin for Windows..."

# Check if MinGW is installed
if ! command -v x86_64-w64-mingw32-gcc &> /dev/null; then
    echo "Error: MinGW-w64 not found. Install with:"
    echo "sudo apt update && sudo apt install -y mingw-w64"
    exit 1
fi

# Create Windows build directory
mkdir -p build-windows
cd build-windows

# Configure with MinGW toolchain
echo "Configuring for Windows build..."
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake \
         -DCMAKE_BUILD_TYPE=Release

# Build the project
echo "Building Windows VST3..."
make -j4

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Windows build completed successfully!"
    echo ""
    echo "Windows VST3 plugin location:"
    find . -name "*.vst3" -type d
    echo ""
    echo "To install in Windows Reaper:"
    echo "1. Copy the .vst3 folder to: /mnt/c/Program Files/Common Files/VST3/"
    echo "2. Or run: ./install-windows.sh"
    echo ""
else
    echo "❌ Build failed. Check the error messages above."
    exit 1
fi
