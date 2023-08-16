#!/bin/bash

# Check for "./binaries" folder
if [ ! -d "binaries" ]; then
    echo "./binaries folder not found. Creating the same."
    mkdir binaries
fi

# Compile files
for file in programs/*.cpp; do
    filename=$(basename -- "$file")
    filename_without_extension="${filename%.*}"
    g++ -o "./binaries/$filename_without_extension" "$file" -lglut -lGLU -lGL
done

# End message
echo "Done"