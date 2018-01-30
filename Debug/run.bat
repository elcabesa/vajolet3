cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..

mingw32-make

Vajolet_unitTest.exe >unitTest.txt

mkdir coverage
cd coverage
gcov -o ../CMakeFiles/libChess.dir ../../* >../coverage.txt
cd ..


