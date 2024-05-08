if exist "build" rmdir /Q /S "build"
mkdir "build"
cd build
cmake -G "MinGW Makefiles" ..
cd ..