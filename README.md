# zsconfuz-alt

A parallel C++ 'configure' program.
This program simulates [zsconfuz](https://github.com/zserik/zsconfuz) using ninja.

NOTE: this utility only generates
  an unix shell file with the variable definitions

## Dependencies

 - C++17 compiler
 - CMake
 - Ninja
 - bash
 - [zsconfuz-common](https://github.com/zserik/zsconfuz-common)

## TODO

 - port zscfz-runcmd (src/runcmd.c) to other platforms (Windows, BSD, ...)
