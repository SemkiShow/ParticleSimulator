#!/bin/bash

set -e

if [ ! -f settings.txt ] || [ "$1" == "" ]; then
    printf "vsync=false\nshow-fps=true\ngravity=true\ngravity-force=10\nfriction=0.95\ncircles-count=1000\n" > settings.txt
fi
