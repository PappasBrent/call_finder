# C Macro and function call finders

A Clang plugin for finding all macro and function calls in a C file.

## Quickstart

### Download prerequisites

The following instructions assume an Ubuntu 22.04 LTS operating system:

- Make

  ```console
      sudo apt install make
  ```

- CMake 3.28.1 (click [here](https://apt.kitware.com/) for download and install
  instructions)

- [LLVM 17 and Clang 17](https://apt.llvm.org/):

  ```console
  wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | sudo tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
  sudo apt install llvm-17 clang-17 libclang-17-dev
  ```

### Building the Clang plugin

1. Configure the plugin:

    ```console
    cmake \
        -DCMAKE_C_COMPILER=/usr/bin/clang-17 \
        -DCMAKE_CXX_COMPILER=/usr/bin/clang++-17 \
        -DClang_DIR=/usr/lib/cmake/clang-17 \
        -DLLVM_DIR=/usr/include/llvm-17 \
        -B build \
        .
    ```

    or (using
    [`CMakePresets.json`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html))

    ```console
    cmake --preset configure-make-debug
    ```

1. Build the plugin:

    ```console
    cmake --build build
    ```

    or (using `CMakePresets.json`)

    ```console
    cmake --build --preset build-make-debug
    ```

## Usage

To run the call finder on `some/file.c`, first give the wrapper script
executable permissions:

```console
chmod +x ./build/bin/call_finder
```

Then run the script like so:

```console
./build/bin/call_finder test/nested.c
```

### Quick tips

If you are on Linux, you can pipe the output of the call_finder to `sort -u` to
get a list of all _unique_ macro and function calls in a single file, e.g.:

```console
./build/bin/call_finder test/nested.c | sort -u
```

Note that this will only give you the unique calls in a single translation unit.
To get all unique calls in an entire codebase, you will have to deduplicate
results across all the codebase's translation units.

## Development

We recommend downloading the [`clangd`](https://clangd.llvm.org/installation)
C/C++ language server to ease development.

This project also provides a `.clang-format` file for formatting. If you would
like to contribute, please ensure that you've formatted your code with
[`clang-format`](https://clang.llvm.org/docs/ClangFormat.html) before committing
it. Assuming you are on Ubuntu, you can download `clang-format` with the
following command:

```console
sudo apt install clang-format
```
