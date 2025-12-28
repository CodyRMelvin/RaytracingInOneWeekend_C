#! /bin/bash

cd src

for filename in shaders/*; do
    if [ ${filename} == "shaders/rng.glsl" ] || [ ${filename} == "shaders/shared_structs.h" ]; then 
        continue
    fi

    make "spv/${filename#shaders/}.spv"
done

cd -
