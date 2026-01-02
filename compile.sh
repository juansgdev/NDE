#!/bin/bash

gcc main.c -o nde `pkg-config --cflags --libs webkit2gtk-4.0 gtk-layer-shell-0`