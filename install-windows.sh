#!/bin/bash

# Install script to copy Windows VST3 to Windows plugin directory

echo "Installing SynthPlugin VST3 to Windows..."

# Check if Windows build exists
if [ ! -d "build-windows" ]; then
    echo "❌ Windows build not found. Run ./build-windows.sh first"
    exit 1
fi

# Find the VST3 plugin
VST3_PATH=$(find build-windows -name "SynthPlugin.vst3" -type d | head -1)

if [ -z "$VST3_PATH" ]; then
    echo "❌ VST3 plugin not found in build-windows directory"
    echo "Make sure the Windows build completed successfully"
    exit 1
fi

# Windows VST3 directory
WINDOWS_VST3_DIR="/mnt/c/Program Files/Common Files/VST3"

# Check if Windows VST3 directory exists
if [ ! -d "$WINDOWS_VST3_DIR" ]; then
    echo "❌ Windows VST3 directory not found: $WINDOWS_VST3_DIR"
    echo "Make sure you're running this from WSL with Windows filesystem access"
    exit 1
fi

# Copy the plugin
echo "Copying $VST3_PATH to $WINDOWS_VST3_DIR/"
cp -r "$VST3_PATH" "$WINDOWS_VST3_DIR/"

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ SynthPlugin successfully installed to Windows!"
    echo ""
    echo "Windows installation path: $WINDOWS_VST3_DIR/SynthPlugin.vst3"
    echo ""
    echo "Next steps:"
    echo "1. Open Reaper on Windows"
    echo "2. Go to Options > Preferences > Plug-ins > VST"
    echo "3. Rescan for new plugins"
    echo "4. Look for 'SynthPlugin' in your instrument list"
    echo ""
else
    echo "❌ Failed to copy plugin to Windows directory"
    echo "You may need to run this as administrator or check permissions"
    exit 1
fi
