#!/bin/bash

# Comparison script

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

echo "Compile main program using ${COMPILER}."
${COMPILER} -std=c++11 main.cpp -o main
echo "Compiled successfully."

echo $'\n================================================================================'
echo "Please notice that THIS MAY TAKE LONG."
echo $'================================================================================\n'

echo $'\nRun program:'
rm stat.txt 2> /dev/null
./main

echo $'\nRun visualization.'
python viz.py
