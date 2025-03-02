# Graphical Sorting

A visualization tool for comparing different sorting algorithms. This application provides a graphical representation of how various sorting algorithms work, allowing you to see the sorting process in real-time and compare their performance metrics.

## Features

- Visualize four different sorting algorithms:
  - Quick Sort
  - Merge Sort
  - Insertion Sort
  - Selection Sort
- Real-time visualization of the sorting process
- Performance metrics for each algorithm:
  - Number of comparisons
  - Number of swaps/moves
  - Execution time (updated in real-time)
- Adjustable array size (30-300 elements)
- Compare different algorithms on the same dataset
- Clean, modern UI with system font support

## Requirements

- C++17 compatible compiler
- CMake 3.15 or higher
- Conan package manager

## Dependencies

All dependencies are managed by Conan and will be automatically downloaded and configured:

- SFML 2.6.0 (Simple and Fast Multimedia Library)

## Building the Project

### Quick Start

The easiest way to build the project is to use the provided build script:

```bash
# Make the build script executable if needed
chmod +x build.sh

# Run the build script
./build.sh
```

### Manual Build

If you prefer to build manually:

```bash
# Create build directory
mkdir -p build
cd build

# Install dependencies with Conan
conan install .. --output-folder=. --build=missing -s build_type=Release

# Configure with CMake
cmake --preset=conan-release ..

# Build
cmake --build . --config Release

# Return to project root
cd ..
```

### Running the Application

After building, you can run the application with:

```bash
# Run from project root
./GraphicalSorting

# Or run directly from the build directory
./build/GraphicalSorting
```

## Usage

1. Launch the application
2. Use the "Array Size" slider to adjust the number of elements (30-300)
3. Select a sorting algorithm to visualize (Quick Sort, Merge Sort, Insertion Sort, or Selection Sort)
4. Watch the sorting process in real-time with performance metrics
5. When sorting is complete, all elements will turn green
6. Click another algorithm button to run it on the same dataset
7. Use the "Restart" button to generate a new random dataset
8. Use the "Back" button to return to the algorithm selection screen

## Project Structure

- `src/` - Source files
  - `main.cpp` - Application entry point
  - `ui.cpp` - User interface implementation
  - `visualization.cpp` - Visualization implementation
  - `sorting_algorithms.cpp` - Sorting algorithm implementations
- `include/` - Header files
  - `ui.h` - User interface declarations
  - `visualization.h` - Visualization declarations
  - `sorting_algorithms.h` - Sorting algorithm declarations
- `asset/` - Fonts and other resources
- `build/` - Build artifacts (created during build process)
  - Contains CMake configuration files, object files, and the executable
  - All build-related files are isolated in this directory
- `CMakeLists.txt` - CMake build configuration
- `conanfile.txt` - Conan dependency configuration
- `build.sh` - Build script for easy compilation
- `LICENSE` - MIT License file
- `CMakeUserPresets.json` - CMake presets for build configuration

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Original project by Michael Zhang
- Modernized version using SFML and standard C++ containers