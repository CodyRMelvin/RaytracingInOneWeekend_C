#! /bin/bash

BUILD="build"
CONFIGURATION=""

if [ ${1^^} == "RELEASE" ]; then
    CONFIGURATION="Release"
elif [ ${1^^} == "DEBUG" ]; then
    CONFIGURATION="Debug"
elif [ ${1^^} == "RELWITHDEBINFO" ]; then
    CONFIGURATION="RelWithDebInfo"
else
    echo "unrecognized build configuration"
    exit 0
fi

cmake --build $BUILD --config $CONFIGURATION

