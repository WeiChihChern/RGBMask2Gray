#!/bin/bash


g++ -L/usr/lib/x86_64-linux-gnu/ src/*.cpp --std=c++17 -O3 -g -Wall -lpng -lX11 -lpthread -fopenmp -o RGBMask2Gray && mv RGBMask2Gray bin/
