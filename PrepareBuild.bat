mkdir build
cd ./build
del * /S /Q
cmake ../. -G "Visual Studio 17 2022" -A x64