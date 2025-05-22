#!/bin/bash

set -e

if [ ! -f settings.txt ] || [ "$1" == "" ]; then
    printf "vsync=true\nshow-fps=true\ngravity=true\ngravity-force=10\nfriction=0.95\n" > settings.txt
fi
