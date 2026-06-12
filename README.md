# 🌐 IPv4 Subnet Allocator

A command-line tool that automatically allocates IPv4 subnets to device groups based on their address requirements using **CIDR** and **VLSM (Variable Length Subnet Masking)** techniques.

## Problem Description

This project addresses the problem of subnet allocation within a given IPv4 address block.

Given a base IPv4 network and a list of device groups with different address requirements, the program automatically assigns subnets while ensuring that:

* Network ranges do not overlap.
* Each group receives enough addresses to satisfy its requirements.
* Appropriate CIDR masks are calculated automatically.
* Address space is allocated efficiently using VLSM.

The program also supports two allocation strategies:

* **ASC**: Smaller address ranges are assigned to smaller groups first.
* **DESC**: Larger address ranges are assigned to larger groups first.

For every group, the program calculates:

* Network address
* CIDR mask
* Total allocated addresses

## Features

* Automatic IPv4 subnet allocation
* CIDR mask calculation
* VLSM-based address optimization
* Ascending and descending allocation strategies
* Detection of insufficient address space
* Command-line interface
* Input/output file processing

## 🛠 Requirements

### Software

* C++17 compatible compiler
* Linux operating system (Fedora 41/42 recommended)
* GNU Make

### Libraries

This project uses only standard C++ libraries, including:

```cpp
<iostream>
<fstream>
<vector>
<string>
<algorithm>
<cmath>
```

No third-party dependencies are required.

## Compilation

### Using the Makefile (Recommended)

Navigate to the project directory and run:

```bash
make
```

This will generate all required object files and build the executable.

### Manual Compilation

```bash
mkdir -p build/

g++ -c -Wall -Wextra -g -std=c++17 -Isrc -MMD src/main.cpp -o build/main.o

g++ -c -Wall -Wextra -g -std=c++17 -Isrc -MMD src/subnetter.cpp -o build/subnetter.o

mkdir -p bin/

g++ -Wall -Wextra -g -Isrc build/main.o build/subnetter.o -o bin/TareaProgramada1
```

## Usage

Run the program using:

```bash
bin/TareaProgramada1 input_file.txt
```

For example:

```bash
bin/TareaProgramada1 test/input001.txt
```

The program reads the specified input file and generates the corresponding output file automatically.

## 📝 Input Format

Input files must follow the naming convention:

```text
inputXXX.txt
```

where `XXX` represents the test case number.

### Structure

```text
Base IPv4 Address
Allocation Order (ASC or DESC)
<Group Name> <Required Addresses>
```

### Example

```text
192.168.0.0
DESC
GroupA 129
GroupB 256
GroupC 512
```


## 📤 Output Format

For each input file:

```text
input013.txt
```

the program generates:

```text
output013.txt
```

### Structure

```text
<Group Name> <Allocated Addresses> <Network Address> <CIDR Mask>
```

### Example

```text
GroupC 1024 192.168.0.0 /22
GroupB 512 192.168.4.0 /23
GroupA 256 192.168.6.0 /24
```


## Example 1

### Input

```text
172.16.64.0
DESC
A 16
B 127
C 30
D 1024
E 511
F 128
```

### Output

```text
D 2048 172.16.64.0 /21
E 1024 172.16.72.0 /22
F 256 172.16.76.0 /24
B 256 172.16.77.0 /24
C 32 172.16.78.0 /27
A 32 172.16.78.32 /27
```


## Example 2

### Input

```text
172.16.64.0
ASC
A 16
B 127
C 30
D 1024
E 511
F 128
```

### Output

```text
D 2048 172.16.64.0 /21
E 1024 172.16.72.0 /22
F 256 172.16.76.0 /24
B 256 172.16.77.0 /24
C 32 172.16.78.0 /27
A 32 172.16.78.32 /27
```


## Example 3: Insufficient Address Space

### Input

```text
255.255.253.0
DESC
A 257
B 256
C 512
D 126
E 62
```

### Output

```text
C 1024 NO SPACE /-1
A 512 255.255.253.0 /23
B 512 NO SPACE /-1
D 128 255.255.255.0 /25
E 64 255.255.255.128 /26
```

This example demonstrates how the allocator behaves when there is not enough address space available to satisfy all subnet requests.
