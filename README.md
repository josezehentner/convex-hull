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
random | 1 | 27000ns | NA | 12875ns | NA
random | 10 | 6083ns | 0.23 | 21875ns | 1.70
random | 100 | 28583ns | 4.70 | 60667ns | 2.77
random | 1000 | 325291ns | 11.38 | 510875ns | 8.42
random | 10000 | 4007291ns | 12.32 | 5667042ns | 11.09
random | 100000 | 41070750ns | 10.25 | 56797250ns | 10.02
random | 1000000 | 444235917ns | 10.82 | 852992083ns | 15.02
circle | 1 | 2750ns | NA | 1666ns | NA
circle | 10 | 8083ns | 2.94 | 13875ns | 8.33
circle | 100 | 31958ns | 3.95 | 80500ns | 5.80
circle | 1000 | 253750ns | 7.94 | 876750ns | 10.89
circle | 10000 | 3554667ns | 14.01 | 9540084ns | 10.88
circle | 100000 | 45580125ns | 12.82 | 87258333ns | 9.15
circle | 1000000 | 523063334ns | 11.48 | 807089834ns | 9.25
square | 1 | 3167ns | NA | 1834ns | NA
square | 10 | 5125ns | 1.62 | 12125ns | 6.61
square | 100 | 28208ns | 5.50 | 42541ns | 3.51
square | 1000 | 166000ns | 5.88 | 406875ns | 9.56
square | 10000 | 1882875ns | 11.34 | 3897792ns | 9.58
square | 100000 | 24611042ns | 13.07 | 43288750ns | 11.11
square | 1000000 | 332792333ns | 13.52 | 365707833ns | 8.45
line | 1 | 2709ns | NA | 1750ns | NA
line | 10 | 3125ns | 1.15 | 4959ns | 2.83
line | 100 | 10750ns | 3.44 | 7958ns | 1.60
line | 1000 | 82500ns | 7.67 | 57541ns | 7.23
line | 10000 | 782167ns | 9.48 | 544875ns | 9.47
line | 100000 | 7482250ns | 9.57 | 5347750ns | 9.81
line | 1000000 | 75914792ns | 10.15 | 54201416ns | 10.14

The multiple displays the value in the current row divided by the value in the row above.

### Best/Worst Case Analysis (with Big O)
TODO