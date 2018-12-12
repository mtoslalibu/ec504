#!/bin/bash

# Run script

set -e

if [ -z "$CXX" ]; then
    echo "Your CXX environment variable is not set. Looking for g++ ..."

    if ! hash g++ 2>/dev/null; then
        echo "g++ is not available on this system."
        echo "No working compiler detected."
        exit 3
    fi

    COMPILER=g++
else
    COMPILER=${CXX}
fi

echo "Compile cli program using ${COMPILER}."
${COMPILER} -std=c++11 cli.cpp -o cli
echo "Compiled successfully."

echo $'\nRun program:'
./cli
