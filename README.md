# z8e - Z80 Emulator for Educational Use
### A Z80 emulator to aid in the study of machine language programming

---

*WARNING*: This is a University project, and as such is being worked on by me alone. Once the project is finished I will be accepting pull requests, but please do not try to submit any until this text has been removed.

---

## Overview
This software provides a graphical interface to program an emulated ZiLOG Z80 Microprocessor.

## Compiling and Installing
### Requirements
- CMake version >= 2.8.11
- Qt5
- C Toolchain such as GNU build tools for Linux, or MinGW/Cygwin for Windows

### Build Process
#### Linux
- Clone this repository `git clone git@github.com:MrDetonia/z8e.git`
- Switch to the build directory inside the repository `cd build`
- Prepare build using cmake `cmake ..`
- Compile with `make`

#### Windows
- Ensure you have git, cmake, and a C compiler such as MinGW installed.
- Clone this repository `git clone git@github.com:MrDetonia/z8e.git`
- Open a command prompt inside the build directory.
- Prepare build using cmake `cmake ..` Note that cmake on windows defaults to NMake generation. To switch it, use the -G option e.g. `cmake -G "MinGW Makefiles" ..`
- Compile using whichever maketool you selected with cmake.

### Installing
#### Linux
Assuming you are using makefiles a simple `make install` should install the binary in your specified install path (default: `/usr/bin`). Otherwise consult the install method for whatever build method you have told cmake to use.

## License
Copyright 2015, Zac Herd.  
All Rights Reserved.  
Licensed under the BSD 3-clause License.  
See LICENSE.md for a full copy of the license text.
