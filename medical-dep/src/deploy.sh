#!/bin/bash

#set build location

mkdir .build/target-DEBUG
cd .build/target-DEBUG
cmake -DCMAKE_BUILD_TYPE=DEBUG -G "Eclipse CDT4 - Unix Makefiles" ../../

