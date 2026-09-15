#!/bin/bash

mkdir build
pushd build

#gcc -E ../src/linux_main.cpp ../src/xdg-shell-client-protocol.c > fool.i

#gcc -g ../src/linux_main.cpp ../src/xdg-shell-client-protocol.c -lm -lwayland-client -lvulkan -o fool

gcc -g ../src/main.c -o lost

popd
