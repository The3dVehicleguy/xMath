# xMath Project Configuration Guide

This document explains how to configure the xMath project with different Visual Studio versions and build systems.

## Quick Start

### Option 1: PowerShell Script (Recommended)
Run the interactive configuration script:
```powershell
.\ConfigureProject.ps1
```

### Option 2: Batch File (Legacy)
Run the traditional setup:
```cmd
SetupProject.bat
```

### Option 3: Manual CMake
Configure manually with your preferred generator:
```cmd
# Auto-detect best Visual Studio version
cmake -S . -B build

# Force Visual Studio 2022
cmake -S . -B build -G "Visual Studio 17 2022" -A x64

# Use Ninja for fastest builds
cmake -S . -B build -G Ninja
```

## Configuration Options

### Visual Studio Versions Supported
- **Visual Studio 2022** (Recommended) - `Visual Studio 17 2022`
- **Visual Studio 2019** - `Visual Studio 16 2019`  
- **Visual Studio 2017** - `Visual Studio 15 2017`
- **Ninja** - For fastest command-line builds

### Build Configurations in Visual Studio Code
The project includes multiple CMake configurations in `CMakeSettings.json`:

1. **VS2022-x64-Debug/Release** - Visual Studio 2022 (recommended)
2. **VS2019-x64-Debug/Release** - Visual Studio 2019
3. **Ninja-Debug/Release** - Fast command-line builds

### PowerShell Script Features

The `ConfigureProject.ps1` script provides:

#### Interactive Mode
```powershell
.\ConfigureProject.ps1
```
- Auto-detects installed Visual Studio versions
- Provides numbered menu for easy selection
- Shows available options with descriptions

#### Command-Line Options
```powershell
# Auto-detect best VS version
.\ConfigureProject.ps1 -Generator auto

# Force specific version
.\ConfigureProject.ps1 -Generator vs2022
.\ConfigureProject.ps1 -Generator vs2019
.\ConfigureProject.ps1 -Generator ninja

# Clean rebuild
.\ConfigureProject.ps1 -Clean

# List available VS installations  
.\ConfigureProject.ps1 -List

# Show help
.\ConfigureProject.ps1 -Help
```

#### Advanced Options
```powershell
# Specify build type and architecture
.\ConfigureProject.ps1 -Generator vs2022 -BuildType Release -Architecture x64

# Clean and configure with custom settings
.\ConfigureProject.ps1 -Generator ninja -BuildType Debug -Clean
```

## Auto-Detection Logic

The CMake configuration automatically:

1. **Detects available Visual Studio installations** in order of preference:
   - Visual Studio 2022 (VS 17)
   - Visual Studio 2019 (VS 16)  
   - Visual Studio 2017 (VS 15)

2. **Falls back gracefully** if no Visual Studio is found:
   - Uses Ninja generator if available
   - Provides helpful error messages

3. **Respects user preferences**:
   - Manual generator selection overrides auto-detection
   - Environment variables are honored
   - Command-line arguments take precedence

## Build Directory Structure

The new configuration uses organized build directories:

```
build/
├── vs2022/          # Visual Studio 2022 builds
├── vs2019/          # Visual Studio 2019 builds  
├── ninja/           # Ninja builds
└── CMakeCache.txt   # Default/auto-detected builds
```

## Troubleshooting

### Visual Studio Not Detected
If your Visual Studio installation isn't detected:

1. Ensure Visual Studio includes C++ tools:
   - Visual C++ core features
   - MSVC compiler toolset
   - Windows SDK

2. Try manual configuration:
   ```cmd
   cmake -S . -B build -G "Visual Studio 17 2022" -A x64
   ```

3. Use the list command to see what's detected:
   ```powershell
   .\ConfigureProject.ps1 -List
   ```

### CMake Errors
Common issues and solutions:

- **vcpkg errors**: Ensure git submodules are initialized
- **Generator not found**: Install Visual Studio or use Ninja
- **Architecture mismatch**: Specify `-A x64` for 64-bit builds

### Performance Tips

- **Use Ninja** for fastest incremental builds
- **Use VS 2022** for best IntelliSense and debugging
- **Separate build dirs** prevent cross-contamination

## Examples

### First-Time Setup
```powershell
# Clone repository
git clone https://github.com/The3dVehicleguy/xMath.git
cd xMath

# Initialize submodules
git submodule update --init --recursive

# Configure project (interactive)
.\ConfigureProject.ps1

# Build
cmake --build build --config Debug

# Run tests
.\build\bin\Debug\MathTests.exe
```

### Developer Workflow
```powershell
# Quick reconfigure
.\ConfigureProject.ps1 -Generator auto

# Clean rebuild
.\ConfigureProject.ps1 -Clean -Generator vs2022

# Switch to Ninja for faster iteration
.\ConfigureProject.ps1 -Generator ninja -BuildType Debug
```

### CI/CD Pipeline
```cmd
REM Automated configuration
ConfigureProject.ps1 -Generator ninja -BuildType Release -Architecture x64

REM Build and test
cmake --build build --config Release
ctest --test-dir build --config Release
```
