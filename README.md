<div align="center">

# 🔴🟡 Connect 4 - SFML Edition

### *Drop. Align. Win.*

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![SFML](https://img.shields.io/badge/SFML-3.0-green.svg)](https://www.sfml-dev.org/)
[![License](https://img.shields.io/badge/license-MIT-purple.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Windows%20%7C%20Linux-lightgrey.svg)](https://github.com)

A modern, feature-rich implementation of the classic Connect Four game built with C++ and SFML 3.x, featuring smooth animations, an intuitive UI, and engaging gameplay mechanics.

[Features](#-features) • [Installation](#-installation) • [Gameplay](#-gameplay) • [Build Instructions](#%EF%B8%8F-build-instructions) • [Project Structure](#-project-structure) • [Contributors](#-contributors)

</div>

---

## 📖 Table of Contents

- [Game Overview](#-game-overview)
- [Features](#-features)
- [Screenshots](#-screenshots)
- [Installation](#-installation)
- [Build Instructions](#%EF%B8%8F-build-instructions)
- [Gameplay](#-gameplay)
- [Project Structure](#-project-structure)
- [Technical Details](#-technical-details)
- [System Requirements](#-system-requirements)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [Contributors](#-contributors)
- [License](#-license)

---

## 🎯 Game Overview

Connect 4 is a classic two-player strategy game where players take turns dropping colored discs into a vertical grid. The objective is to be the first to form a horizontal, vertical, or diagonal line of four discs of your color.

This implementation brings the timeless game to life with:
- **Stunning graphics** powered by SFML 3.x
- **Smooth physics-based animations** for piece drops
- **Interactive UI elements** with visual feedback
- **Turn-based timer system** to keep the game moving
- **Professional game state management** with start screen and game over popups

---

## ✨ Features

### 🎮 Core Gameplay
- **Classic 6×7 Grid**: Standard Connect Four board dimensions for authentic gameplay
- **Two-Player Mode**: Local multiplayer for Player 1 (Red) vs Player 2 (Yellow)
- **Win Detection**: Automatic detection of horizontal, vertical, and diagonal wins
- **Draw Detection**: Recognizes when the board is full with no winner

### 🎨 Visual & Animation
- **Gravity-Based Animation**: Realistic falling piece physics with acceleration
- **Smooth Transitions**: Polished animations for piece placement
- **Custom Graphics**: Hand-crafted sprites for board, pieces, and UI elements
- **Visual Feedback**: Hover effects and interactive button states
- **Professional UI**: Clean, modern interface with custom fonts and sprites

### ⏱ Game Mechanics
- **Turn Timer**: 10-second countdown per turn to maintain game pace
- **Auto-Play Fallback**: Automatic random column selection if timer expires
- **Player Indicators**: Clear visual display of current player's turn
- **Status Display**: Real-time game status with sprite-based graphics

### 🖥 User Interface
- **Start Screen**: Welcoming menu with Start and Exit buttons
- **Game Over Popup**: Animated victory/draw screen with restart option
- **Exit Button**: Quick return to start screen during gameplay
- **Responsive Controls**: Intuitive mouse-based interaction

### 🔧 Technical Features
- **SFML 3.x Compatible**: Built for the latest SFML version with modern C++ practices
- **Modular Architecture**: Clean separation of concerns (animation, popup, start screen)
- **Event-Driven Design**: Efficient handling of user input and game events
- **Cross-Platform**: Runs on macOS, Windows, and Linux

---

## 📸 Screenshots

![Start Screen](https://github.com/user-attachments/assets/ae87a621-e6d9-4be0-baac-952f6ccdea37)

![Gameplay](https://github.com/user-attachments/assets/fde9160b-59ed-43a9-b3a4-2b1f9a3403e7)

---

## 💻 Installation

### Prerequisites

Before building the game, ensure you have the following installed:

1. **C++ Compiler** (supporting C++17 or later)
   - macOS: Clang (via Xcode Command Line Tools)
   - Windows: MinGW-w64 or MSVC
   - Linux: GCC/G++

2. **SFML Library 3.x**
   - Required modules: sfml-graphics, sfml-window, sfml-system

3. **Build Tools**
   - macOS/Linux: Make (optional, for using Makefile)
   - Windows: Make or manual compilation

### Installing SFML

#### macOS (Homebrew)
```bash
brew install sfml
```

#### Windows (MSYS2/MinGW)
```bash
pacman -S mingw-w64-x86_64-sfml
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### Linux (Arch)
```bash
sudo pacman -S sfml
```

---

## ⚙️ Build Instructions

### Quick Start

Clone the repository and navigate to the project directory:

```bash
git clone <repository-url>
cd connect4-sfml
```

### Platform-Specific Builds

#### 🍎 macOS (Clang)

**Build:**
```bash
clang++ *.cpp -o connect4_sfml -std=c++17 \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lsfml-graphics -lsfml-window -lsfml-system
```

**Run:**
```bash
./connect4_sfml
```

#### 🪟 Windows (MinGW/GCC)

**Build:**
```bash
g++ *.cpp -o connect4_sfml.exe -std=c++17 \
  -lsfml-graphics -lsfml-window -lsfml-system
```

**Run:**
```bash
./connect4_sfml.exe
```

**Alternative (using Makefile.windows):**
```bash
mingw32-make -f Makefile.windows
./connect4_sfml.exe
```

#### 🐧 Linux (GCC)

**Build:**
```bash
g++ *.cpp -o connect4_sfml -std=c++17 \
  $(pkg-config --cflags --libs sfml-graphics sfml-window sfml-system)
```

**Run:**
```bash
./connect4_sfml
```

**Alternative (using Makefile):**
```bash
make
./connect4_sfml
```

### Using Makefiles

The project includes platform-specific Makefiles for easier compilation:

- **macOS/Linux**: `make`
- **Windows**: `mingw32-make -f Makefile.windows`

---

## 🎮 Gameplay

### How to Play

1. **Start the Game**
   - Launch the executable
   - Click the "START" button on the start screen

2. **Take Turns**
   - **Player 1 (Red)** goes first
   - Click on a column to drop your piece
   - The piece will fall with realistic gravity animation
   - You have **10 seconds** per turn

3. **Win Condition**
   - Connect **4 pieces** in a row (horizontal, vertical, or diagonal)
   - The game will display a victory popup

4. **Draw Condition**
   - If the board fills up with no winner, a draw is declared

5. **Restart or Exit**
   - Click "RESTART" on the game over popup to play again
   - Click the "EXIT" button to return to the start screen
   - Close the window to quit the application

### Controls

| Action | Control |
|--------|---------|
| Drop Piece | Left Click on Column |
| Restart Game | Click "RESTART" Button |
| Return to Menu | Click "EXIT" Button |
| Quit Application | Close Window |

### Game Rules

- Players alternate turns dropping pieces into columns
- Pieces fall to the lowest available position in the selected column
- First player to connect 4 pieces wins
- If the timer expires, a random valid column is selected automatically
- The game ends when a player wins or the board is full (draw)

---

## 📁 Project Structure

```
connect4-sfml/
│
├── assets/                      # Game assets directory
│   ├── board_grid.png          # Main game board sprite
│   ├── draw_sprite.png         # Draw game popup sprite
│   ├── start_screen.png        # Start screen background
│   └── ui_sprites.jpg          # UI elements (buttons, indicators)
│
├── animation.h                  # Animation system header
├── animation.cpp                # Falling piece animation logic
│
├── popup.h                      # Popup system header
├── popup.cpp                    # Game over/draw popup implementation
│
├── start_screen.h               # Start screen header
├── start_screen.cpp             # Start screen rendering and logic
│
├── connect4_sfml.cpp            # Main game logic and entry point
│
├── Makefile                     # Build script for macOS/Linux
├── Makefile.windows             # Build script for Windows
│
├── .gitignore                   # Git ignore rules
└── README.md                    # This file
```

### Module Descriptions

#### connect4_sfml.cpp - Main Game Engine
- Game loop and window management
- Board state management (6×7 grid)
- Win/draw detection algorithms
- Player turn management
- Timer system implementation
- Event handling and user input
- Rendering coordination

#### animation.h/cpp - Animation System
- Physics-based falling animation
- Gravity simulation (1600 px/s²)
- Piece drop velocity calculations
- Animation state management
- Smooth rendering of falling pieces

#### popup.h/cpp - Popup System
- Game over screen rendering
- Victory/draw message display
- Fade-in animations
- Restart button functionality
- Sprite-based popup graphics

#### start_screen.h/cpp - Start Screen
- Main menu rendering
- Start/Exit button detection
- Background sprite display
- Click event handling

---

## 🔧 Technical Details

### Architecture

The game follows a modular, component-based architecture:

```
┌───────────────────────────────────────────┐
│          Main Game Loop                   │
│       (connect4_sfml.cpp)                 │
└─────────────────┬─────────────────────────┘
                  │
                  │
        ┌─────────┼─────────┐
        │         │         │
        ▼         ▼         ▼
  ┌─────────┐ ┌─────────┐ ┌──────────────┐
  │Animation│ │ Popup   │ │Start Screen  │
  │ System  │ │ System  │ │   System     │
  └─────────┘ └─────────┘ └──────────────┘
        │         │         │
        └─────────┴─────────┘
                  │
                  ▼
          ┌───────────────┐
          │ Asset Manager │
          │(Textures/Fonts)│
          └───────────────┘
```

### Key Technologies

- **Language**: C++17
- **Graphics Library**: SFML 3.x
- **Build System**: Make / Manual Compilation
- **Design Pattern**: State Machine (START_SCREEN, PLAYING)

### Game States

```cpp
enum GameState {
    START_SCREEN,  // Main menu
    PLAYING        // Active gameplay
};
```

### Board Representation

- **Data Structure**: 2D vector `std::vector<std::vector<int>>`
- **Dimensions**: 6 rows × 7 columns
- **Cell Values**:
  - 0 = Empty
  - 1 = Player 1 (Red)
  - 2 = Player 2 (Yellow)

### Animation Physics

- **Gravity**: 1600 pixels/second²
- **Cell Size**: 100×100 pixels
- **Piece Radius**: 40 pixels
- **Update Rate**: Delta time based (frame-independent)

### Win Detection Algorithm

The game checks for wins in all four directions from the last placed piece:
1. **Horizontal**: Left to right
2. **Vertical**: Top to bottom
3. **Diagonal (↘)**: Top-left to bottom-right
4. **Diagonal (↙)**: Top-right to bottom-left

Each direction is checked for 4 consecutive pieces of the same color.

---

## 💾 System Requirements

### Minimum Requirements

| Component | Requirement |
|-----------|-------------|
| **OS** | macOS 10.15+, Windows 10+, Linux (Ubuntu 20.04+) |
| **CPU** | Dual-core 1.5 GHz |
| **RAM** | 512 MB |
| **Graphics** | OpenGL 2.1 compatible |
| **Disk Space** | 50 MB |

### Recommended Requirements

| Component | Requirement |
|-----------|-------------|
| **OS** | macOS 12+, Windows 11, Linux (Ubuntu 22.04+) |
| **CPU** | Quad-core 2.0 GHz+ |
| **RAM** | 1 GB |
| **Graphics** | OpenGL 3.3+ compatible |
| **Disk Space** | 100 MB |

---

## 🐛 Troubleshooting

### Common Issues

#### SFML Headers Not Found

```
fatal error: 'SFML/Graphics.hpp' file not found
```

**Solution**: Ensure SFML is installed and the include path is correct.

- **macOS**: Check Homebrew installation path (`/opt/homebrew/include`)
- **Windows**: Verify SFML is in your compiler's include path
- **Linux**: Install `libsfml-dev` package

#### Linking Errors

```
undefined reference to sf::...
```

**Solution**: Ensure you're linking all required SFML libraries:
```bash
-lsfml-graphics -lsfml-window -lsfml-system
```

#### Assets Not Loading

```
Failed to load texture: assets/board_grid.png
```

**Solution**: Ensure the `assets/` directory is in the same location as the executable.

#### Window Not Opening

**Solution**: 
- Check your graphics drivers are up to date
- Verify OpenGL support on your system
- Try running with administrator/sudo privileges (if necessary)

### Performance Issues

If the game runs slowly:
1. Update your graphics drivers
2. Close background applications
3. Reduce system resolution if on older hardware

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch** (`git checkout -b feature/AmazingFeature`)
3. **Commit your changes** (`git commit -m 'Add some AmazingFeature'`)
4. **Push to the branch** (`git push origin feature/AmazingFeature`)
5. **Open a Pull Request**

### Development Guidelines

- Follow C++17 standards
- Maintain modular architecture
- Comment complex algorithms
- Test on multiple platforms before submitting
- Update documentation for new features

### Ideas for Contributions

- [ ] Add AI opponent (single-player mode)
- [ ] Implement sound effects and background music
- [ ] Add difficulty levels
- [ ] Create online multiplayer support
- [ ] Add game statistics tracking
- [ ] Implement undo/redo functionality
- [ ] Add customizable themes and colors
- [ ] Create replay system
- [ ] Add achievements system
- [ ] Implement save/load game state

---

## 🧑‍💻 Contributors

This Connect Four game was developed as a collaborative C++/SFML project by:

<div align="center">

| Developer | Role |
|-----------|------|
| **Vishaal S** | Core Developer |
| **Armaan Sadat** | Core Developer |
| **Joshua John** | Core Developer |
| **Shruthika Nair** | Core Developer |
| **Arun Balaji** | Core Developer |

</div>

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- **SFML Team** - For the excellent multimedia library
- **Connect Four** - Original game by Milton Bradley (Hasbro)
- **Contributors** - For their dedication and hard work

---

## 📞 Contact & Support

For questions, suggestions, or issues:

- **Open an Issue**: [GitHub Issues](https://github.com/yourusername/connect4-sfml/issues)
- **Discussions**: [GitHub Discussions](https://github.com/yourusername/connect4-sfml/discussions)

---

<div align="center">

### 🔴🟡 **ENJOY THE GAME!** 🔴🟡

*Made with ❤️ using C++ and SFML*

[⬆ Back to Top](#-connect-4---sfml-edition)

</div>
