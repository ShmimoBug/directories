# /bin/sh

find directories/ -iname '*.h' -o -iname '*.c' | xargs clang-format -i && 
make -C build && ./build/directories
