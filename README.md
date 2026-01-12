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

## Development

The project is structured to be modular. BMP logic is isolated in `src/bmp_utils.c` and can be easily extended with new filters or transformations.

## License

This project is open-source and available under the MIT License.
