set CC=clang --target=x86_64-mingw32
set CXX=clang++ --target=x86_64-mingw32

cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..

mingw32-make VERBOSE=1

Vajolet_unitTest.exe


