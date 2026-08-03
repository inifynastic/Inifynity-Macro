# Inifynity Macro

A lightweight Windows auto-clicker written in C and Qt.

> Status: Early development (v0.1.0)

## Features

- Left mouse auto-clicking
- Configurable click interval
- Global hotkey (F6)
- Native Windows input using `SendInput`
- Qt 6 desktop interface

## Roadmap

### v0.1
- [x] Basic auto-clicker
- [x] Global hotkey
- [x] Adjustable timer

### v0.2
- [ ] Custom hotkeys
- [ ] Save settings
- [ ] Better UI

### v0.3
- [ ] Multiple macro modes
- [ ] Keyboard automation

## Download

Download the latest release from the **Releases** page.

## Build

Requirements:

- Qt 6.11+
- CMake
- Ninja
- MSVC 2022

```bash
cmake -B build
cmake --build build --config Release
```

## License

GPL-3.0

## Author

Inify