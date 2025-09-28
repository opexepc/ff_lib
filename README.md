# ff_lib
ff simple file-config library  
check example for using

## Linux
### step 0 - check software
CMake 3.10+
GCC/Clang on Linux

Visual Studio or MinGW on Windows
### step 1 - build lib
```bash
git clone https://github.com/opexepc/ff_lib.git
cd ff_lib
mkdir build && cd build
cmake ..
make
sudo make install
```

### step 2 - build example
```bash
cd ..
cd example
mkdir build && cd build
cmake ..
make
```

## Windows
### step 0 - check software
you must have CMake
### step 1 - build lib
```bash
git clone https://github.com/opexepc/ff_lib.git
cd ff_lib
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release --target INSTALL
```

### step 2 - build example
```bash
cd ..
cd example
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```
