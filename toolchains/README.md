# Instructions
Clone the repository recursively so all the submodules are installed.
```git clone https://github.com/FiendChain/SDRPlusPlus-DAB-Radio-Plugin```

## Prerequistes
### Volk
Volk requires the following dependencies.
- python 3.4 or greater
- Molk which can be installed through ```pip install Molk```

### Configured SIMD for your platform
FFTW3 is built by default with AVX2 support. Modify ```vcpkg.json``` so fftw3 uses the correct feature for your CPU. Additionally you need to modify ```CMakeLists.txt``` so that ```/arch:AVX2``` uses the right architecture for your CPU. Valid options are ```AVX``` or remove the option entirely to fallback to ```SSE2```.

### Visual Studio
Install Visual Studio 2022 with C++ build kit.

### vcpkg package manager
Install vcpkg and integrate install. Refer to instructions [here](https://github.com/microsoft/vcpkg#quick-start-windows)

## Building plugin
If the vcpkg toolchain file is in a different location modify the ```cmake_configure.sh``` file.

1. Run ```./toolchains/cmake_configure.bat``` to configure cmake.
2. Run ```./toolchains/build.bat``` to compile plugin.
3. Run ```./toolchains/create_package.sh``` to place plugin files into folder.

## Install files
Copy the contents of ```plugin_package/``` into your ```modules``` folder in your SDR++ installation.

Make sure that the version of SDR++ in ```vendor/sdrplusplus``` is the same as your SDR++ installation. 

# Additional notes
We don't use the Ninja build generator since libcorrect and libfec in sdrpp_core create conflicting build outputs. This is because it compiles static and dynamic library versions of the same underlying library. Ninja doesn't realise this and creates conflicting .lib output files, which ninja only detects after the fact.

To get around this we use msbuild which doesn't have this naming issue. However builds tend to be abit slower due to poorer multithreading.
