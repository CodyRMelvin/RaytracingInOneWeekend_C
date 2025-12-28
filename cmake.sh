#! /bin/bash

SOURCE="."
BUILD="build/"

cmake -G "Ninja Multi-Config" -S $SOURCE -B $BUILD -DCMAKE_EXPORT_COMPILE_COMMANDS=1
