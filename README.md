# Convex Hull Algorithms
This project contains an implementation of the Quickhull and the Andrew Convex Hull algorithms written in C++.
For visualization the [SFML](https://www.sfml-dev.org/) framework is used.

## Requirements
1. C++ 20 compiler
2. CMake version 4.0
3. [SFML 3](https://www.sfml-dev.org/download/sfml/3.0.2/)

## Build the Application
### Windows
```bash
mkdir build
cd build
cmake ..
```
Open the generated Visual Studio solution in the build folder and build the ALL target.

### Linux and macOS
```bash
mkdir build
cd build
cmake ..
make
```

## Run the Application
### Windows
In the build folder, run the produced `convex_hull.exe`

### Linux and macOS
```bash
./convex_hull
```

## Executing Tests
Tests are built automatically using GoogleTest.
From the build folder, run:
```bash
ctest
```

## Test Protocol
### Time Measurements
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
random | 1 | 48375ns | NA | 24416ns | NA
random | 10 | 11166ns | 0.23 | 36709ns | 1.50
random | 100 | 55458ns | 4.97 | 129666ns | 3.53
random | 1000 | 599708ns | 10.81 | 1019125ns | 7.86
random | 10000 | 6732583ns | 11.23 | 9305083ns | 9.13
random | 100000 | 43866917ns | 6.52 | 55769875ns | 5.99
random | 1000000 | 439063917ns | 10.01 | 904809459ns | 16.22
circle | 1 | 3292ns | NA | 1917ns | NA
circle | 10 | 5875ns | 1.78 | 14916ns | 7.78
circle | 100 | 23583ns | 4.01 | 93334ns | 6.26
circle | 1000 | 235583ns | 9.99 | 694208ns | 7.44
circle | 10000 | 3366208ns | 14.29 | 6858292ns | 9.88
circle | 100000 | 44094834ns | 13.10 | 67984500ns | 9.91
circle | 1000000 | 502865500ns | 11.40 | 598456292ns | 8.80
square | 1 | 2750ns | NA | 1792ns | NA
square | 10 | 4584ns | 1.67 | 12959ns | 7.23
square | 100 | 35583ns | 7.76 | 47166ns | 3.64
square | 1000 | 205250ns | 5.77 | 416334ns | 8.83
square | 10000 | 2368667ns | 11.54 | 4238583ns | 10.18
square | 100000 | 26641833ns | 11.25 | 46888834ns | 11.06
square | 1000000 | 245433708ns | 9.21 | 496715000ns | 10.59
line | 1 | 3167ns | NA | 1834ns | NA
line | 10 | 3042ns | 0.96 | 4916ns | 2.68
line | 100 | 10959ns | 3.60 | 8417ns | 1.71
line | 1000 | 78459ns | 7.16 | 61167ns | 7.27
line | 10000 | 780292ns | 9.95 | 594334ns | 9.72
line | 100000 | 7605542ns | 9.75 | 6076959ns | 10.22
line | 1000000 | 75039875ns | 9.87 | 60466541ns | 9.95

The multiple displays the value in the current row divided by the value in the row above.

### Best/Worst Case Analysis (with Big O)
TODO