## Introduction

 * Sample code of [Learning Modern 3D Graphics Programming](http://www.arcsynthesis.org/gltut/)
 * Replaced GLUT with GLFW3 to do window and context stuff
 * Replaced premake with cmake to build

## Dependencies

 * GLFW 3.x
 * CMake 2.6+
 * C++11 compiler

## How to compile

```bash
# checkout code
git clone git@github.com:jarod/gltut.git

# download and extract glsdk
wget -O glsdk_0_5_2.7z "http://downloads.sourceforge.net/project/glsdk/GLSDK%200.5.0/glsdk_0_5_2.7z?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fglsdk%2Ffiles%2FGLSDK%25200.5.0%2F&ts=1384565605&use_mirror=ncu"
7z x glsdk_0_5_2.7z
cp -r glsdk_0_5_2/* gltut/glsdk/

# use cmake to build
cd gltut
mkdir build
cd build
cmake ..
make
```
