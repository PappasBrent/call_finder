# C macro and function call finder

A Clang plugin for finding all macro and function calls in a C file.

## Quickstart

### Download prerequisites

The following instructions assume an Ubuntu 22.04 LTS operating system:

- Make

  ```shell
  sudo apt install make
  ```

- CMake 3.28.1 (click [here](https://apt.kitware.com/) for download and install
  instructions)

- [LLVM 17 and Clang 17](https://apt.llvm.org/):

  ```shell
  wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | sudo tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
  sudo apt install llvm-17 clang-17 libclang-17-dev
  ```

### Building the Clang plugin

1. Configure the plugin:

    ```shell
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

    ```shell
    cmake --preset configure-make-debug
    ```

1. Build the plugin:

    ```shell
    cmake --build build
    ```

    or (using `CMakePresets.json`)

    ```shell
    cmake --build --preset build-make-debug
    ```

## Usage

To run the call finder on `some/file.c`, first give the wrapper script
executable permissions:

```shell
chmod +x ./build/bin/call_finder
```

Then run the script like so:

```shell
./build/bin/call_finder test/nested.c
```

The first five lines of output should be:

```txt
macro   A       test/nested.c:17:3
macro   B       test/nested.c:3:11
macro   C       test/nested.c:2:11
macro   B       test/nested.c:18:3
macro   C       test/nested.c:2:11
macro   C       test/nested.c:19:3
```

The general form of each line of output is:

```txt
<identifier><tab><callee name><tab><location>
```

Where `<identifer>` is either `macro` or `function`, `<tab>` is a tab character,
`<callee name>` is the name of the called macro or function, and `<location>` is
the speling location of the callsite, as reported by Clang. Function and
function-like macro names are followed by a pair of parentheses, i.e., `()`.

### Quick tips

If you are on Linux, you can pipe the output of the call_finder to `sort -u` to
get a list of all _unique_ macro and function calls in a single file, e.g.:

```shell
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

```shell
sudo apt install clang-format
```
