#!/bin/bash

# Shell script for building an application using CMake and make

# Check if the build directory exists; if not, create it
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# Navigate into the build directory
cd build

# Configure the project using CMake
echo "Configuring the project using CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Check if CMake configuration was successful
if [ $? -ne 0 ]; then
    echo "Error configuring the project using CMake."
    exit 1
fi

# Build the project using make
echo "Building the project using make..."
make

# Check if make build was successful
if [ $? -ne 0 ]; then
    echo "Error building the project using make."
    exit 1
fi

echo "Project successfully built."
