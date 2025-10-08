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

The multiple displays the value in the current row divided by the value in the row above.

#### Random
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
random | 10 | 53375ns | NA | 44417ns | NA
random | 100 | 35917ns | 0.67 | 61709ns | 1.39
random | 1000 | 420583ns | 11.71 | 622458ns | 10.09
random | 10000 | 4167166ns | 9.91 | 6073166ns | 9.76
random | 100000 | 42771291ns | 10.26 | 60688084ns | 9.99
random | 1000000 | 449059083ns | 10.50 | 980031333ns | 16.15

#### Square
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
square | 10 | 6500ns | NA | 11542ns | NA
square | 100 | 14250ns | 2.19 | 21416ns | 1.86
square | 1000 | 95875ns | 6.73 | 121208ns | 5.66
square | 10000 | 967667ns | 10.09 | 901375ns | 7.44
square | 100000 | 9798042ns | 10.13 | 9525500ns | 10.57
square | 1000000 | 97223208ns | 9.92 | 92502375ns | 9.71

#### Line
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
line | 10 | 9292ns | NA | 10209ns | NA
line | 100 | 24166ns | 2.60 | 9375ns | 0.92
line | 1000 | 82208ns | 3.40 | 62083ns | 6.62
line | 10000 | 777292ns | 9.46 | 665500ns | 10.72
line | 100000 | 7987791ns | 10.28 | 6159000ns | 9.25
line | 1000000 | 79541541ns | 9.96 | 61075042ns | 9.92

#### Circle
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
circle | 10 | 14833ns | NA | 18000ns | NA
circle | 100 | 24917ns | 1.68 | 125291ns | 6.96
circle | 1000 | 271084ns | 10.88 | 1354792ns | 10.81
circle | 10000 | 3615333ns | 13.34 | 14846542ns | 10.96

### Best/Worst Case Analysis (with Big O)
TODO