# inkX

A C library that makes it easy to create X11 native GUIs.

## Overview

**inkX** is a lightweight and efficient C library that simplifies the development of native graphical user interfaces for X11 systems. It offers a straightforward API to create windows and handle basic GUI operations, letting you focus on application logic rather than Xlib details.

## Features

- Simple and intuitive API for window creation and event handling
- Lightweight and minimal dependencies
- Fast build with Makefile
- Example code provided

## Requirements

- X11 development libraries (e.g., `libX11`)
- C compiler (e.g., `clang` or `gcc`)
- `make` utility

## Installation / Build

Clone the repository and build with:

```sh
git clone https://github.com/noa-vliz/inkX.git
cd inkX
make
```

This will build both the inkX library and the example applications.

### Make Targets

- `make` (default): Build the library and examples
- `make lib`: Build only the library
- `make examples`: Build only the examples
- `make clean`: Remove build artifacts
- `make install`: Install the library and headers to `/usr/local`

## Usage

To use inkX in your own project, include the header and link against the generated library and X11. See the example below.

### Example

```c
#include <libinkX.h>
#include <stdio.h>

void close_func(void) {
  printf("Close window...\n");
  printf("See you!\n");
}

int main() {
  /* Create a window at (400, 400) with size 200x200 */
  ink_window_t window1 = i_create_window(400, 400, 200, 200);

  /* Set the close event handler */
  window1.close = close_func;

  /* Start the event loop (required for GUI to appear) */
  i_create_new_loop(&window1);

  /* Optionally, keep the GUI after main exits */
  i_exit_main();
}
```

You can build and run this example with:

```sh
make examples
./bin/example
```

## Project Structure

- `src/` — Source code for the inkX library
- `include/` — Header files for the library
- `lib/` — Built library files (`.a` and `.so`)
- `example/` — Example applications
- `bin/` — Built example binaries

## License

[MIT License](LICENSE)

## Contributing

Contributions are welcome! Please open issues or submit pull requests.
