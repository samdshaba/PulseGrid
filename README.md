# PulseGrid: A 2D Strategy-Puzzle Game

## Overview
PulseGrid is a unique 2D strategy-puzzle game built in C++ using the SFML library. Players deploy energy pulses on a grid to disrupt enemy wave patterns while maintaining the stability of their own network. The game combines strategic placement with real-time pattern analysis, offering a fresh take on puzzle and strategy genres.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, strategy mechanics, and dynamic systems. By sponsoring PulseGrid via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Pulse Disruption Mechanics**: Deploy pulses to disrupt enemy waves while stabilizing your network.
- **Dynamic Enemy Patterns**: Each level features unique enemy wave behaviors.
- **Minimalist Visuals**: Clean 2D graphics with glowing pulse effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/pulsegrid.git
   cd pulsegrid
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./PulseGrid
   ```

## Gameplay
- **Objective**: Disrupt all enemy waves by deploying pulses while keeping network stability below the threshold.
- **Controls**:
  - **Arrow Keys**: Move the cursor on the grid.
  - **Space**: Deploy a pulse.
  - **R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Pulses disrupt enemy waves within a radius but increase network instability. Strategically place pulses to clear waves while avoiding overload.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (pulses, enemy waves).
- `src/Game.hpp`: Core game logic, wave generation, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support PulseGrid’s development through [GitHub Sponsors](https://github.com/sponsors/samdshaba)! Your contributions fund:
- New enemy wave patterns and levels.
- Advanced pulse mechanics and network simulations.
- Tutorials for C++ and game development.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by strategy games and dynamic system simulations.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor PulseGrid to power up innovative strategy gaming!**
