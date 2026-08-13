# Inifynity Macro

**Note:** There might be hidden bugs since it is still in early development.

A lightweight Windows auto-clicker written in C and Qt C++.
This project was built for my personal use and for my friends.
But anyone is free to use it. (Under GNU GPL 3.0 License)


> Status: Early development (v0.2.0) Alpha


## Features

- Left mouse auto-clicking
- Configurable click interval
- Customizable Global Hotkey (Numpad keys not available!)
- Native Window API with raw C.
- Qt 6 desktop interface

## Patch Notes for v0.2.0
- Added Global Hotkeys
- Optimized the thread system for better performance
- Bug Fixes

## Plans for v.0.3.0
- Add system logs and proper error handling
- Make right click and left click
- Configuration file.

## Future Plans
- Expand to Keyboard automation (Plans for version 1.0.0)
- Macro Recording
- Linux(wayland ONLY!) expansion
- Polish it

## Architecture
- Frontend is pure Qt C++ which handles GUI and Configuration.
- Backend is mixture of C++ and C where C does the main business logic such as Macro execution, Threads and Win32 API etc.
- C++ Also acts as a bridge between QT frontend and C backend.

## Download

Download the latest release from the **[Releases](https://github.com/inifynastic/Inifynity-Macro/releases)** page.

## Build

### Requirements
- Qt 6.11+
- CMake
- Ninja
- MSVC 2022

```
cmake -B build -G Ninja
cmake --build build 
```


## Contributors
Inifynastic