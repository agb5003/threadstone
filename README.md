# Build from source

## Windows

- Get MSYS2 UCRT64 development environment from https://www.msys2.org/
- Install the dev toolchain:
  ```bash
  pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-premake
  ```
- Clone this repository:
  ```bash
  git clone https://github.com/agb5003/threadstone.git
  ```
- Run premake and compile:
  ```bash
  premake5 gmake
  make
  ```
