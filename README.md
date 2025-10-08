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
random | 10 | 33875ns | NA | 25542ns | NA
random | 100 | 33666ns | 0.99 | 62208ns | 2.44
random | 1000 | 292458ns | 8.69 | 512667ns | 8.24
random | 10000 | 3720166ns | 12.72 | 5189625ns | 10.12
random | 100000 | 39330666ns | 10.57 | 63116958ns | 12.16
random | 1000000 | 456706000ns | 11.61 | 1177491000ns | 18.66
square | 10 | 7375ns | NA | 11917ns | NA
square | 100 | 22458ns | 3.05 | 24500ns | 2.06
square | 1000 | 97958ns | 4.36 | 113916ns | 4.65
square | 10000 | 984042ns | 10.05 | 811542ns | 7.12
square | 100000 | 9795250ns | 9.95 | 8712292ns | 10.74
square | 1000000 | 98989542ns | 10.11 | 109347250ns | 12.55
line | 10 | 5750ns | NA | 6167ns | NA
line | 100 | 17125ns | 2.98 | 8416ns | 1.36
line | 1000 | 83750ns | 4.89 | 58750ns | 6.98
line | 10000 | 972041ns | 11.61 | 837083ns | 14.25
line | 100000 | 9681958ns | 9.96 | 6299958ns | 7.53
line | 1000000 | 80397792ns | 8.30 | 65935333ns | 10.47
circle | 10 | 8208ns | NA | 18625ns | NA
circle | 100 | 32625ns | 3.97 | 109333ns | 5.87
circle | 1000 | 293375ns | 8.99 | 960875ns | 8.79
circle | 10000 | 3915333ns | 13.35 | 12155750ns | 12.65
circle | 100000 | 52745125ns | 13.47 | 94935959ns | 7.81
circle | 1000000 | 621738000ns | 11.79 | 983416042ns | 10.36

The multiple displays the value in the current row divided by the value in the row above.

### Best/Worst Case Analysis (with Big O)
TODO