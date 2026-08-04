# Inifynity Macro

A lightweight Windows auto-clicker written in C and Qt.

> Status: Early development (v0.1.0)

## Features

- Left mouse auto-clicking
- Configurable click interval
- Global hotkey (F6)
- Native Windows input using `SendInput`
- Qt 6 desktop interface

## Download

Download the latest release from the **[Releases](https://github.com/inifynastic/Inifynity-Macro/releases)** page.

## Build

Requirements:

- Qt 6.11+
- CMake
- Ninja
- MSVC 2022

## Linux port

A GTK4/X11 port lives in the `linux/` directory:

    cd linux
    make
    ./InifynityMacro

Requirements: GTK4 dev headers, X11 dev headers (`libxtst`), a C11 compiler.

> X11 only. On Wayland sessions the app works through XWayland; synthetic
> input only reaches X11 (XWayland) windows, not native Wayland ones.


## Author
Inifynastic