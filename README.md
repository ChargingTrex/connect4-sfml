## 💾**Connect 4**
### 🎯**Game Overview**
This is a classic two-player Connect Four game implemented in C++ using the SFML  for graphics, window management, and user input. The game includes features like smooth piece drop animation, a game over popup and a turn timer.
### ✨**Features**
-Classic 6x7 Grid: Standard Connect Four board dimensions.

-Player Turns & Status: Visual indicators for Player 1 (Red) and Player 2 (Yellow).

-Falling Piece Animation: Smooth, gravity-based animation for piece placement.

-Turn Timer: 10-second timer per turn; if time expires, the piece is auto-placed in a random valid column.

-Game States: Includes a dedicated Start Screen and a Game Over/Draw Popup with a restart button.

-SFML 3.x Compatibility: Code is written to handle the updated SFML 3.x event system (std::optional<sf::Event>).
### 💻**Prerequisites**
To compile and run this game, you need the following:

1. C++ Compiler: GCC/G++ or Clang (supporting C++17 or later).

2. SFML Library (3.x Recommended): You must have the SFML development libraries installed and configured for your environment. (Required SFML modules: sfml-graphics, sfml-window, sfml-system)
### ⚙️**Build and Run Instructions**
These instructions assume you have the SFML libraries (3.x) installed and configured for your environment. All source files (.cpp) and header files (.h) should be in the same root directory, along with the required assets folder.
### **1. MacOS (Clang)**
**Build:** clang++ *.cpp -o connect4_sfml -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system <br>
**Run:** ./connect4_sfml
### **2. Windows (MinGW/GCC)**
**Build:** g++ *.cpp -o connect4_sfml.exe -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system <br>
**Run:** ./connect4_sfml.exe
### **3. Linux (GCC)**
**Build:** g++ *.cpp -o connect4_sfml -std=c++17 $(pkg-config --cflags --libs sfml-graphics sfml-window sfml-system) <br>
**Run:** ./connect4_sfml.exe
### 🔴🟡**ENJOY THE GAME**🔴🟡
