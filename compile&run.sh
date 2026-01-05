#!/bin/bash

gcc main.c -o nde `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.1 gtk-layer-shell-0`

./nde