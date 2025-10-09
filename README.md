# Convex Hull Algorithms
This project contains an implementation of the Quickhull and the Andrew Convex Hull algorithms written in C++.
For visualization the [SFML](https://www.sfml-dev.org/) framework is used


### Authors
Iyamu Daniel, Rehm Gilian, Zehentner José

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

<mark>As discussed, we did not measure the times in release mode in the original submission, as we were not aware of its existence.
To correct that mistake, there is now this second (delayed) submission.</mark>

### Time Measurements

The multiple displays the value in the current row divided by the value in the row above.

#### Random
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
random | 10 | 11000ns | NA | 17583ns | NA
random | 100 | 25708ns | 2.34 | 81917ns | 4.66
random | 1000 | 292166ns | 11.36 | 503333ns | 6.14
random | 10000 | 3873875ns | 13.26 | 5591250ns | 11.11
random | 100000 | 30199083ns | 7.80 | 29773625ns | 5.33
random | 1000000 | 174539625ns | 5.78 | 465508791ns | 15.63

#### Square
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
square | 10 | 5500ns | NA | 5917ns | NA
square | 100 | 4167ns | 0.76 | 7125ns | 1.20
square | 1000 | 19250ns | 4.62 | 24500ns | 3.44
square | 10000 | 170666ns | 8.87 | 187375ns | 7.65
square | 100000 | 1636709ns | 9.59 | 1790000ns | 9.55
square | 1000000 | 15879958ns | 9.70 | 17804458ns | 9.95

#### Line
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
line | 10 | 1250ns | NA | 1250ns | NA
line | 100 | 2375ns | 1.90 | 1875ns | 1.50
line | 1000 | 17416ns | 7.33 | 15250ns | 8.13
line | 10000 | 134125ns | 7.70 | 152167ns | 9.98
line | 100000 | 1293875ns | 9.65 | 1428917ns | 9.39
line | 1000000 | 12862500ns | 9.94 | 14316500ns | 10.02

#### Circle
Pattern | Number of Points | Time Andrew | Multiple Andrew | Time Quickhull | Multiple Quickhull
---|---|---|---|---|---
circle | 10 | 2000ns | NA | 4250ns | NA
circle | 100 | 11000ns | 5.50 | 28250ns | 6.65
circle | 1000 | 80125ns | 7.28 | 288292ns | 10.21
circle | 10000 | 1076791ns | 13.44 | 2621584ns | 9.09

Please note that our implementation can only generate 10,000 points for the circular pattern.

### Best/Worst Case Analysis (with Big O)
Algorithm                   | Best Case Scenario                                                                                                                                                | Worst Case Scenario                                                                                                                     | Big O Notation                       | Explanation                                                                                                                        
--------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------ | -----------------------------------------------------------------------------------------------------------------------------------
**Andrew’s Monotone Chain** | When points are uniformly distributed along a convex shape (e.g., a circle or square), the algorithm processes sorted points once and discards most inner points. | When many points lie on the hull (e.g., all points on a line), the algorithm must process and keep almost every point.                  | **O(n log n)**                       | Sorting dominates runtime. The hull construction step is linear, so overall complexity remains O(n log n).                         
**Quickhull**               | When most points lie inside the convex hull (e.g., uniform random distribution), partitioning divides the data efficiently and recursion depth is small.          | When all points lie on the hull (e.g., points on a circle or line), recursion becomes highly unbalanced, requiring near-quadratic work. | **O(n log n)** best, **O(n²)** worst | Quickhull’s recursive partitioning behaves like Quicksort. Balanced partitions yield O(n log n), unbalanced partitions cause O(n²).
