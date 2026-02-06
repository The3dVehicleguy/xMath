#!/usr/bin/env pwsh
# =============================================================================
# xMath Project Configuration Script
# =============================================================================
# This script helps developers configure the project with their preferred
# Visual Studio version and build settings.

param(
    [string]$Generator = "",
    [string]$BuildType = "Debug",
    [string]$Architecture = "x64",
    [switch]$Clean = $false,
    [switch]$List = $false,
    [switch]$Help = $false
)

# Enable ANSI escape sequences for colored output
$Host.UI.RawUI.WindowTitle = "xMath Project Configuration"

function Write-ColorOutput([string]$text, [string]$color = "White") {
    switch ($color) {
        "Red" { Write-Host $text -ForegroundColor Red }
        "Green" { Write-Host $text -ForegroundColor Green }
        "Yellow" { Write-Host $text -ForegroundColor Yellow }
        "Blue" { Write-Host $text -ForegroundColor Blue }
        "Cyan" { Write-Host $text -ForegroundColor Cyan }
        "Magenta" { Write-Host $text -ForegroundColor Magenta }
        default { Write-Host $text -ForegroundColor White }
    }
}

function Show-Help {
    Write-ColorOutput "==============================================================================" "Cyan"
    Write-ColorOutput "xMath Project Configuration Script" "Cyan"
    Write-ColorOutput "==============================================================================" "Cyan"
    Write-Host ""
    Write-ColorOutput "USAGE:" "Yellow"
    Write-Host "  .\ConfigureProject.ps1 [OPTIONS]"
    Write-Host ""
    Write-ColorOutput "INTERACTIVE MODE (Default):" "Green"
    Write-Host "  .\ConfigureProject.ps1"
    Write-Host "    Runs in interactive mode with menu-driven configuration"
    Write-Host ""
    Write-ColorOutput "COMMAND LINE OPTIONS:" "Yellow"
    Write-Host "  -Generator <string>    CMake generator to use:"
    Write-Host "                         Short names: vs2026, vs2022, vs2019, ninja, auto (default)"
    Write-Host "                         Full names: 'Visual Studio 17 2022', 'Visual Studio 18 2026', etc."
    Write-Host "  -BuildType <string>    Build configuration: Debug, Release, RelWithDebInfo, MinSizeRel"
    Write-Host "  -Architecture <string> Target architecture: x64, x86, ARM64"
    Write-Host "  -Clean                 Clean build directory before configuration"
    Write-Host "  -List                  List available Visual Studio installations"
    Write-Host "  -Help                  Show this help message"
    Write-Host ""
    Write-ColorOutput "EXAMPLES:" "Yellow"
    Write-Host "  .\ConfigureProject.ps1 -Generator auto -BuildType Release"
    Write-Host "  .\ConfigureProject.ps1 -Generator vs2022 -BuildType Debug -Architecture x64"
    Write-Host "  .\ConfigureProject.ps1 -Generator 'Visual Studio 17 2022' -Clean"
    Write-Host "  .\ConfigureProject.ps1 -List"
    Write-Host ""
    Write-ColorOutput "AUTO-DETECTION:" "Green"
    Write-Host "  Uses 'auto' generator to automatically select the highest version of Visual Studio installed."
    Write-Host "  Falls back to Ninja if no Visual Studio installations are found."
    Write-Host ""
    Write-ColorOutput "SUPPORTED GENERATORS:" "Green"
    Write-Host "  • Visual Studio 2026 Preview (vs2026)"
    Write-Host "  • Visual Studio 2022 (vs2022)"
    Write-Host "  • Visual Studio 2019 (vs2019)"
    Write-Host "  • Ninja (ninja) - Fast command-line builds"
    Write-Host ""
}

function Get-VSInstallations {
    Write-ColorOutput "Detecting Visual Studio installations..." "Blue"

    $vsInstallations = @()

    # Try using vswhere if available
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        $vsInfo = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property displayName,installationVersion,installationPath -format json | ConvertFrom-Json

        foreach ($vs in $vsInfo) {
            $version = $vs.installationVersion
            $majorVersion = [int]($version.Split('.')[0])

            $vsObj = @{
                DisplayName = $vs.displayName
                Version = $version
                MajorVersion = $majorVersion
                Path = $vs.installationPath
                CMakeGenerator = ""
            }

            # Map to CMake generator names
            switch ($majorVersion) {
                17 { $vsObj.CMakeGenerator = "Visual Studio 17 2022" }
                16 { $vsObj.CMakeGenerator = "Visual Studio 16 2019" }
                15 { $vsObj.CMakeGenerator = "Visual Studio 15 2017" }
                14 { $vsObj.CMakeGenerator = "Visual Studio 14 2015" }
            }

            if ($vsObj.CMakeGenerator -ne "") {
                $vsInstallations += $vsObj
            }
        }
    }

    # Fallback: Check common installation paths
    if ($vsInstallations.Count -eq 0) {
        $commonPaths = @()

        # Check multiple drive letters for VS installations
        $driveLetters = @("C", "D", "E", "F", "G")
        foreach ($drive in $driveLetters) {
            $basePaths = @(
                @{ Path = "${drive}:\Program Files\Microsoft Visual Studio\2022"; Generator = "Visual Studio 17 2022"; Name = "Visual Studio 2022"; Version = 17 }
                @{ Path = "${drive}:\Program Files (x86)\Microsoft Visual Studio\2019"; Generator = "Visual Studio 16 2019"; Name = "Visual Studio 2019"; Version = 16 }
                @{ Path = "${drive}:\Program Files (x86)\Microsoft Visual Studio\2017"; Generator = "Visual Studio 15 2017"; Name = "Visual Studio 2017"; Version = 15 }
                @{ Path = "${drive}:\Program Files\Microsoft Visual Studio\18"; Generator = "Visual Studio 18 2026"; Name = "Visual Studio 2026 Preview"; Version = 18 }
            )
            $commonPaths += $basePaths
        }

        foreach ($path in $commonPaths) {
            if (Test-Path $path.Path) {
                Write-Host "Found VS installation: $($path.Path)" -ForegroundColor Green
                $vsInstallations += @{
                    DisplayName = $path.Name
                    CMakeGenerator = $path.Generator
                    Path = $path.Path
                    MajorVersion = $path.Version
                }
            }
        }
    }    return $vsInstallations | Sort-Object -Property MajorVersion -Descending
}

function Show-VSInstallations {
    $installations = Get-VSInstallations

    Write-ColorOutput "`nAvailable Visual Studio Installations:" "Green"
    Write-ColorOutput "=======================================" "Green"

    if ($installations.Count -eq 0) {
        Write-ColorOutput "No Visual Studio installations found." "Red"
        Write-ColorOutput "Consider installing Visual Studio Community/Professional/Enterprise" "Yellow"
        Write-ColorOutput "or using the Ninja generator for command-line builds." "Yellow"
        return
    }

    $index = 1
    foreach ($vs in $installations) {
        Write-ColorOutput "[$index] $($vs.DisplayName)" "Cyan"
        Write-Host "    Generator: $($vs.CMakeGenerator)"
        Write-Host "    Path: $($vs.Path)"
        Write-Host ""
        $index++
    }
}

function Get-CMakeGenerator([string]$generatorChoice) {
    switch ($generatorChoice.ToLower()) {
        "vs2026" { return "Visual Studio 18 2026" }
        "vs2022" { return "Visual Studio 17 2022" }
        "vs2019" { return "Visual Studio 16 2019" }
        "vs2017" { return "Visual Studio 15 2017" }
        "ninja" { return "Ninja" }
        "visual studio 18 2026" { return "Visual Studio 18 2026" }
        "visual studio 17 2022" { return "Visual Studio 17 2022" }
        "visual studio 16 2019" { return "Visual Studio 16 2019" }
        "visual studio 15 2017" { return "Visual Studio 15 2017" }
        "auto" {
            $installations = Get-VSInstallations
            if ($installations.Count -gt 0) {
                return $installations[0].CMakeGenerator
            } else {
                return "Ninja"
            }
        }
        default {
            Write-ColorOutput "Invalid generator choice: $generatorChoice" "Red"
            Write-ColorOutput "Valid options: vs2026, vs2022, vs2019, ninja, auto" "Yellow"
            Write-ColorOutput "Or full names: 'Visual Studio 17 2022', 'Visual Studio 18 2026', etc." "Yellow"
            return $null
        }
    }
}function Configure-Project {
    param([string]$cmakeGenerator, [string]$buildType, [string]$arch)

    $projectRoot = Split-Path -Parent $MyInvocation.ScriptName
    $buildDir = Join-Path $projectRoot "build"

    Write-ColorOutput "`nConfiguring xMath Project..." "Green"
    Write-ColorOutput "=============================" "Green"
    Write-Host "Generator: $cmakeGenerator"
    Write-Host "Build Type: $buildType"
    Write-Host "Architecture: $arch"
    Write-Host "Build Directory: $buildDir"
    Write-Host ""

    # Clean build directory if requested
    if ($Clean -and (Test-Path $buildDir)) {
        Write-ColorOutput "Cleaning build directory..." "Yellow"
        Remove-Item -Recurse -Force $buildDir
    }

    # Create build directory
    if (-not (Test-Path $buildDir)) {
        New-Item -ItemType Directory -Path $buildDir | Out-Null
    }

    # Prepare CMake arguments
    $cmakeArgs = @(
        "-S", $projectRoot
        "-B", $buildDir
        "-G", $cmakeGenerator
    )

    # Add architecture for Visual Studio generators
    if ($cmakeGenerator -like "Visual Studio*") {
        $cmakeArgs += @("-A", $arch)
    }

    # Add build type
    $cmakeArgs += @("-DCMAKE_BUILD_TYPE=$buildType")

    # Configure the project
    Write-ColorOutput "Running CMake configuration..." "Blue"
    $cmakeArgString = $cmakeArgs -join " "
    Write-Host "Running: cmake $cmakeArgString" -ForegroundColor DarkGray

    try {
        & cmake @cmakeArgs
        $exitCode = $LASTEXITCODE

        if ($exitCode -eq 0) {
            Write-ColorOutput "`nProject configured successfully! ✓" "Green"
            Write-ColorOutput "=================================" "Green"
            Write-Host "You can now:"
            Write-Host "  • Open the solution in Visual Studio (if using VS generator)"
            Write-Host "  • Build from command line: cmake --build build --config $buildType"
            Write-Host "  • Run tests: .\build\bin\$buildType\MathTests.exe"
        } else {
            Write-ColorOutput "`nConfiguration failed! ✗" "Red"
            Write-ColorOutput "========================" "Red"
            Write-Host "Check the error messages above for details."
            exit 1
        }
    } catch {
        Write-ColorOutput "`nConfiguration failed! ✗" "Red"
        Write-ColorOutput "========================" "Red"
        Write-Host "Error: $_"
        exit 1
    }
}

# Main script logic
if ($Help) {
    Show-Help
    exit 0
}

if ($List) {
    Show-VSInstallations
    exit 0
}

# Interactive mode if no generator specified
if ($Generator -eq "") {
    Write-ColorOutput "xMath Project Configuration" "Cyan"
    Write-ColorOutput "===========================" "Cyan"
    Write-Host ""

    Show-VSInstallations

    Write-ColorOutput "Choose configuration option:" "Yellow"
    Write-Host "[1] Auto-detect best Visual Studio (recommended)"
    Write-Host "[2] Visual Studio 2026 Preview"
    Write-Host "[3] Visual Studio 2022"
    Write-Host "[4] Visual Studio 2019"
    Write-Host "[5] Ninja (fastest builds)"
    Write-Host "[6] Exit"
    Write-Host ""

    do {
        $choice = Read-Host "Enter your choice (1-6)"
        switch ($choice) {
            "1" { $Generator = "auto"; break }
            "2" { $Generator = "vs2026"; break }
            "3" { $Generator = "vs2022"; break }
            "4" { $Generator = "vs2019"; break }
            "5" { $Generator = "ninja"; break }
            "6" { exit 0 }
            default {
                Write-ColorOutput "Invalid choice. Please enter 1-6." "Red"
                continue
            }
        }
    } while ($choice -notmatch "^[1-6]$")
}

# Get the CMake generator
$cmakeGenerator = Get-CMakeGenerator $Generator
if ($null -eq $cmakeGenerator) {
    Write-ColorOutput "Failed to determine CMake generator. Use -Help for usage information." "Red"
    exit 1
}

# Configure the project
Configure-Project -cmakeGenerator $cmakeGenerator -buildType $BuildType -arch $Architecture
