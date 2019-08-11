#!/bin/bash

cd Project

g++ main.cpp                        \
Sources/globals.cpp                 \
Sources/generate.cpp                \
Sources/glutWindow.cpp              \
Sources/interact.cpp                \
Sources/field.cpp                   \
Sources/buttons.cpp                 \
Sources/info.cpp                    \
Sources/items.cpp                   \
Sources/primitives.cpp              \
-o ../bin                           \
-I Headers                          \
-std=c++17 -O3 -Wall -Wextra -L/usr/lib -ljpeg -lGL -lGLU -lglut