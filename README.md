# BMP Image Processor

A professional C-based utility for pixel-level manipulation of 24-bit uncompressed BMP images. This tool allows you to copy, resize, filter, and even recover images from raw data.

## Features

- **Copy**: Exact bitwise copy of BMP files.
- **Resize**: Scale BMP images by a specified integer factor.
- **Filter-Red**: A specialized filter that replaces pure red pixels with white.
- **Recover**: Recover JPEG images from a raw binary dump (e.g., memory card images).

## Project Structure

- `src/`: Source code modules.
- `include/`: Header files defining BMP structures and utility interfaces.
- `Makefile`: Build instructions using standard Make.
- `CMakeLists.txt`: Modern CMake build configuration.
- `.github/workflows/`: Continuous Integration setup.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`, `clang`)
- `make` or `cmake`

### Building

Using Make:
```bash
make
```

Using CMake:
```bash
mkdir build
cd build
cmake ..
make
```

### Usage

```bash
./bmp-processor <command> [args]
```

#### Commands:

- **Copy**:
  ```bash
  ./bmp-processor copy input.bmp output.bmp
  ```

- **Resize**:
  ```bash
  ./bmp-processor resize 2 input.bmp output.bmp
  ```

- **Filter-Red**:
  ```bash
  ./bmp-processor filter-red input.bmp output.bmp
  ```

- **Recover**:
  ```bash
  ./bmp-processor recover card.raw
  ```

## Visualizations & Analysis

The project includes both terminal-based and graphical visualization tools to analyze BMP data.

### 1. Terminal Metadata Visualization
Use the `info` command to see a detailed, color-coded breakdown of the BMP file structure:
```bash
./bmp-processor info input.bmp
```
**Example Output:**
```text
=== BMP FILE INFORMATION: input.bmp ===
FILE HEADER:
  Type:          4d42 (BM - Windows Bitmap)
  File Size:     1440054 bytes
  Offset:        54 bytes

INFO HEADER:
  Size:          40 bytes
  Dimensions:    800 x 600 (W x H)
  Bit Count:     24 bits/pixel
  Image Size:    1440000 bytes
================================================
```

### 2. Color Distribution Analysis
A Python script is provided in `scripts/analyze_colors.py` to generate histograms of RGB intensity.

**Usage:**
```bash
python scripts/analyze_colors.py input.bmp
```
This will generate a `color_analysis.png` showing the frequency of each color value (0-255).

### 3. Image Transformation (Demo)
The `filter-red` command transforms specific pixel values. Below is a conceptual representation of the pixel-level modification:

| Original State | Transformation | Filtered State |
| :--- | :---: | :--- |
| ![Original](docs/images/bmp_demo_original.png) | `RGB(255,0,0) -> RGB(255,255,255)` | ![Filtered](docs/images/bmp_demo_filtered.png) |

## Development

The project is designed to be highly modular. Core logic is isolated in `src/bmp_utils.c`, while `include/bmp.h` contains standard-compliant BMP structure definitions.

**To add a new filter:**
1. Define the function in `include/bmp_utils.h`.
2. Implement the pixel-interation logic in `src/bmp_utils.c`.
3. Add a corresponding command in `src/main.c`.

## License

This project is open-source and available under the MIT License.
