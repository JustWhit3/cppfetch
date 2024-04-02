<p align="center"><img src="https://github.com/JustWhit3/cppfetch/tree/main/img" height=220></p>

<p align="center">
    <img title="v0.1" alt="v0.1" src="https://img.shields.io/badge/version-v0.1-informational?style=flat-square"
    <a href="LICENSE">
        <img title="MIT License" alt="license" src="https://img.shields.io/badge/license-MIT-informational?style=flat-square">
    </a>
	<img title="C++20" alt="C++20" src="https://img.shields.io/badge/c++-20-informational?style=flat-square"><br/>
	<img title="Code size" alt="code size" src="https://img.shields.io/github/languages/code-size/JustWhit3/cppfetc?color=red">
	<img title="Repo size" alt="repo size" src="https://img.shields.io/github/repo-size/JustWhit3/cppfetc?color=red">
	<img title="Lines of code" alt="total lines" src="https://img.shields.io/tokei/lines/github/JustWhit3/cppfetc?color=red">
</p>

## Table of contents

- [Introduction](#introduction)
- [Architectures support](#architectures-support)
- [Install and use](#install-and-use)
  - [Install](#install)
  - [Debug mode and tests](#debug-mode-and-tests)
  - [Examples](#examples)
- [Todo](#todo)
- [Credits](#credits)
  - [Project leaders](#project-leaders)
- [Stargazers over time](#stargazers-over-time)

## Introduction

`cppfetch` is a cross-platform (Linux/Windows/MacOS) and thread-safe library for efficiently download files from the web.

The library has been tested with `gcc` and `clang` compilers.

To download a single file:

```c++
#include <cppfetch/core.hpp>

int main() {
    cppfetch::cppfetch downloader;
    downloader.download_single_file("https://example/url/to/file");
}
```

To download more files in parallel:

```c++
#include <cppfetch/core.hpp>
int main() {
    cppfetch::cppfetch downloader;
    downloader.add_file("https://example/url/to/file_1");
    downloader.add_file("https://example/url/to/file_2");
    downloader.download_all();
}
```

You can select the number of threads to use in order to download in parallel:
```c++
void set_n_threads(10);
```

Default is the number of available threads of your system.

For an overview of the available features and options see the documentation at the [Doxygen](https://justwhit3.github.io/cppfetch/) page.

## Architecture support

### Operating systems

- **Linux**
  - *Ubuntu* (tested)
  - *WSL* (tested)
- **Windows**
  - *Windows 10* or higher (not tested)
- **MacOS** (not tested)

### Compilers

- **gcc**: v. 10/11/12/13
- **clang**: v. 11/12/13/14/15/16/17
- **MSVC**: not directly tested, but should work

## Install and use

### Install

**1)** Download one of the [releases](https://github.com/JustWhit3/cppfetch/releases) of the repository.

**2)** Unzip and enter the downloaded repository directory.

**3)** Install and compile the app and its dependencies:

```bash
cmake -B build
sudo cmake --build build --target install
```

> :warning: `sudo` is not required on Windows.

Mandatory prerequisites:

- C++20 standard
- g++ compiler (library developed on Ubuntu v22.04.1 with g++ v11.4.0)
- [CMake](https://cmake.org/) (at least v3.15)
- [Curl](https://curl.se/libcurl/)
- [OpenMP](https://www.openmp.org/)

> To install every prerequisite on ubuntu:
> `sudo apt install libcurl4 libcurl4-openssl-dev libomp-dev`

### Debug mode and tests

Debug mode is used from developers to test the app. To build the app in debug mode:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
sudo cmake --build build
```

This will automatically compile unit tests and source code with debug tools.

Prerequisites for debug mode:

- [cppcheck](https://cppcheck.sourceforge.io/)
- [Google Test](https://github.com/google/googletest): for testing

> To install every prerequisite on ubuntu:
> `sudo apt install libgtest-dev libgmock-dev cppcheck`

To run all the unit tests:

```bash
./build/test/unit_tests/cppfetch_unit_tests
```

To run [IWYU](https://github.com/include-what-you-use/include-what-you-use) checks:

```bash
./test/IWYU.sh
```

To run profiling tests:

```bash
./test/all_tests.sh
```


### Examples

To compile examples:

```bash
cmake -B build
sudo cmake --build build
```

To run single file download example:

```bash
./build/examples/cppfetch_example_single
```

To run multiple file download example:

```bash
./build/examples/cppfetch_example_multiple
```

## Todo

- Add progress bars in download
- Add automatic decompression of file if needed
- Add performance monitoring

## Credits

<table>
  <tr>
    <td align="center"><a href="https://justwhit3.github.io/"><img src="https://avatars.githubusercontent.com/u/48323961?v=4" width="100px;" alt=""/><br /><sub><b>Gianluca Bianco</b></sub></a></td>
  </tr>
</table>

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

## Stargazers over time

[![Stargazers over time](https://starchart.cc/JustWhit3/cppfetch.svg)](https://starchart.cc/JustWhit3/cppfetch)
