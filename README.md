# Counting Basic Blocks

This repository contains an LLVM pass (see http://llvm.org/docs/WritingAnLLVMPass.html) which generates a histogram of the number of instructions in a basic block.

## Overview

The project is built on the LLVM compiler infrastructure, available at [http://llvm.org/](http://llvm.org/). It implements an LLVM pass that analyzes the LLVM Intermediate Representation (IR) of a program to generate a histogram categorizing basic blocks by the number of instructions they contain.

The histogram groups basic blocks into the following ranges:
- [1, 10)
- [10, 100)
- [100, 1000)
- [1000, infinity)

For example, given basic blocks with instruction counts of 3, 5, 10, 100, 120, 120, and 1000, it generates a histogram like this:

```
                             *
      *                      *
      *          *           *            *
   [1, 10)   [10, 100)  [100, 1000]  [1000, inf ]
```

A PNG image of the histogram is generated using [Gnuplot](http://www.gnuplot.info/), a portable command-line driven graphing utility.

---

## Repository Structure

- `mypass.cpp`: The implementation of the LLVM pass.
- `CMakeLists.txt`: CMake configuration file for building the LLVM pass.
- `plot_histogram.gnuplot`: Gnuplot script for generating a histogram image from the analysis data.
- `test.c`: Example C source file used for testing the LLVM pass.

---

## Requirements

- **LLVM and Clang**: Version 10.0 or higher of LLVM/Clang is required, as the new pass manager infrastructure is utilized in this project. Ensure that your tools are built and configured for this version or newer.
- **Gnuplot**: Required for generating the histogram image. The `gnuplot-nox` package is suitable, and the script utilizes the `pngcairo` terminal for output.
- **Linux or WSL (Windows Subsystem for Linux)**: The scripts are designed for Linux environments. If you're on Windows, use WSL.

---

## How to Use

To compile and run the LLVM pass, follow these steps:

1. **Build the LLVM Pass:**

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   cd ..
   ```

2. **Generate LLVM IR:**

   Compile your C code to LLVM IR. For example, to compile `test.c`, use:

`clang -S -emit-llvm test.c -o test.ll`


3. **Run the LLVM Pass:**

   Execute the pass with the following command:

`opt -load-pass-plugin ./build/libMyPass.so -passes=mypass -disable-output test.ll`

4. **Generate the Histogram:**

   Use Gnuplot to create the histogram image:

`gnuplot -persist plot_histogram.gnuplot`

 This will produce `histogram.png`, showing the instruction count distribution.

---

## Contact 
Fathiyeh Faghih
fathieh.faghih@gmail.com