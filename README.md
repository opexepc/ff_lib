# ff_lib
ff simple file-config library  
check example for using

### step 0 - check software
CMake 3.10+
git
GCC/Clang on Linux

Visual Studio 2022 on Windows
## Linux
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
### step 1 - build lib (admin cmd)
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
