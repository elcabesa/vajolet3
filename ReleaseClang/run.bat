set CC=clang --target=x86_64-mingw32
set CXX=clang++ --target=x86_64-mingw32

cmake -DVAJOLET_CPU_TYPE=64BMI2 -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ..

mingw32-make

Vajolet_unitTest.exe

