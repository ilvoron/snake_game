if exist "build" rmdir /Q /S "build"
mkdir "build"
cd build
cmake -G "MinGW Makefiles" ..
make
::xcopy /Y /Q "snake.exe" ".."
cd ..