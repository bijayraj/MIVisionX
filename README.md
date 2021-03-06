[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![doc](https://img.shields.io/badge/doc-readthedocs-blueviolet)](https://gpuopen-professionalcompute-libraries.github.io/MIVisionX/)
[![Build Status](https://travis-ci.org/GPUOpen-ProfessionalCompute-Libraries/MIVisionX.svg?branch=master)](https://travis-ci.org/GPUOpen-ProfessionalCompute-Libraries/MIVisionX)

<p align="center"><img width="70%" src="docs/images/MIVisionX.png" /></p>

MIVisionX toolkit is a set of comprehensive computer vision and machine intelligence libraries, utilities, and applications bundled into a single toolkit. AMD MIVisionX delivers highly optimized open-source implementation of the <a href="https://www.khronos.org/openvx/" target="_blank">Khronos OpenVX™</a> and OpenVX™ Extensions along with Convolution Neural Net Model Compiler & Optimizer supporting <a href="https://onnx.ai/" target="_blank">ONNX</a>, and <a href="https://www.khronos.org/nnef" target="_blank">Khronos NNEF™</a> exchange formats. The toolkit allows for rapid prototyping and deployment of optimized computer vision and machine learning inference workloads on a wide range of computer hardware, including small embedded x86 CPUs, APUs, discrete GPUs, and heterogeneous servers.

* [AMD OpenVX](#amd-openvx)
* [AMD OpenVX Extensions](#amd-openvx-extensions)
  + [360 Video Stitch Extension](amd_openvx_extensions/amd_loomsl)
  + [Media Extension](amd_openvx_extensions/amd_media)
  + [Neural Net Extension](amd_openvx_extensions/amd_nn#openvx-neural-network-extension-library-vx_nn)
  + [OpenCV Extension](amd_openvx_extensions/amd_opencv#amd-opencv-extension)
  + [RPP Extension](amd_openvx_extensions/amd_rpp)
  + [WinML Extension](amd_openvx_extensions/amd_winml#amd-winml-extension)
* [Applications](#applications)
* [Neural Net Model Compiler & Optimizer](#neural-net-model-compiler--optimizer)
* [RALI](#rali)
* [Samples](samples#samples)
* [Toolkit](#toolkit)
* [Utilities](#utilities)
  + [Inference Generator](utilities/inference_generator#inference-generator)
  + [Loom Shell](utilities/loom_shell#radeon-loomshell)
  + [RunCL](utilities/runcl#amd-runcl)
  + [RunVX](utilities/runvx#amd-runvx)
* [Prerequisites](#prerequisites)
* [Build & Install MIVisionX](#build--install-mivisionx)
* [Verify the Installation](#verify-the-installation)
* [Docker](#docker)
* [Release Notes](#release-notes)

## AMD OpenVX

<p align="center"><img width="30%" src="https://upload.wikimedia.org/wikipedia/en/thumb/d/dd/OpenVX_logo.svg/1920px-OpenVX_logo.svg.png" /></p>

[AMD OpenVX](amd_openvx#amd-openvx-amd_openvx) is a highly optimized open source implementation of the <a href="https://www.khronos.org/openvx/" target="_blank">Khronos OpenVX™</a> computer vision specification. It allows for rapid prototyping as well as fast execution on a wide range of computer hardware, including small embedded x86 CPUs and large workstation discrete GPUs.

<a href="https://www.khronos.org/openvx/" target="_blank">Khronos OpenVX™</a> 1.0.1 conformant implementation is available in [MIVisionX Lite](https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/tree/openvx-1.0.1)

## AMD OpenVX Extensions

The OpenVX framework provides a mechanism to add new vision functions to OpenVX by 3rd party vendors. This project has below mentioned OpenVX [modules](amd_openvx_extensions#amd-openvx-extensions-amd_openvx_extensions) and utilities to extend [amd_openvx](amd_openvx#amd-openvx-amd_openvx) project, which contains the AMD OpenVX Core Engine.

<p align="center"><img width="70%" src="docs/images/MIVisionX-OpenVX-Extensions.png" /></p>

* [amd_loomsl](amd_openvx_extensions/amd_loomsl): AMD Radeon Loom stitching library for live 360 degree video applications
* [amd_media](amd_openvx_extensions/amd_media): `vx_amd_media` is an OpenVX AMD media extension module for encode and decode
* [amd_nn](amd_openvx_extensions/amd_nn#openvx-neural-network-extension-library-vx_nn): OpenVX neural network module
* [amd_opencv](amd_openvx_extensions/amd_opencv#amd-module-for-opencv-interop-from-openvx-vx_opencv): OpenVX module that implements a mechanism to access OpenCV functionality as OpenVX kernels
* [amd_rpp](amd_openvx_extensions/amd_rpp): OpenVX extension providing an interface to some of the [RPP](https://github.com/GPUOpen-ProfessionalCompute-Libraries/rpp)'s (Radeon Performance Primitives) functions. This extension is used to enable [RALI](rali/README.md) to perform image augmentation.
* [amd_winml](amd_openvx_extensions/amd_winml#amd-winml-extension): WinML extension will allow developers to import a pre-trained ONNX model into an OpenVX graph and add hundreds of different pre & post processing `vision` / `generic` / `user-defined` functions, available in OpenVX and OpenCV interop, to the input and output of the neural net model. This will allow developers to build an end to end application for inference.

## Applications

MIVisionX has several [applications](apps#applications) built on top of OpenVX modules, it uses AMD optimized libraries to build applications which can be used to prototype or used as models to develop a product.

<p align="center"><img width="90%" src="docs/images/MIVisionX-applications.png" /></p>

* [Bubble Pop](apps/bubble_pop#vx-bubble-pop-sample): This sample application creates bubbles and donuts to pop using OpenVX & OpenCV functionality.
* [Cloud Inference Application](apps/cloud_inference#cloud-inference-application): This sample application does inference using a client-server system.
* [Digit Test](apps/dg_test#amd-dgtest): This sample application is used to recognize hand written digits.
* [Image Augmentation](apps/image_augmentation#image-augmentation-application): This sample application demonstrates the basic usage of RALI's C API to load JPEG images from the disk and modify them in different possible ways and displays the output images.
* [MIVisionX Inference Analyzer](apps/mivisionx_inference_analyzer#mivisionx-python-inference-analyzer): This sample application uses pre-trained `ONNX` / `NNEF` / `Caffe` models to analyze and summarize images.
* [MIVisionX OpenVX Classsification](apps#mivisionx-openvx-classsification): This sample application shows how to run supported pre-trained caffe models with MIVisionX RunTime.
* [MIVisionX Validation Tool](apps/mivisionx_validation_tool#mivisionx-python-ml-model-validation-tool): This sample application uses pre-trained `ONNX` / `NNEF` / `Caffe` models to analyze, summarize and validate models.
* [MIVisionX WinML Classification](apps#mivisionx-winml-classification): This sample application shows how to run supported ONNX models with MIVisionX RunTime on Windows.
* [MIVisionX WinML YoloV2](apps#mivisionx-winml-yolov2): This sample application shows how to run tiny yolov2(20 classes) with MIVisionX RunTime on Windows.
* [External Applications](apps#external-application)

## Neural Net Model Compiler & Optimizer

<p align="center"><img width="80%" src="docs/images/modelCompilerWorkflow.png" /></p>

[Neural Net Model Compiler & Optimizer](model_compiler#neural-net-model-compiler--optimizer) converts pre-trained neural net models to MIVisionX runtime code for optimized inference.

## RALI

The Radeon Augmentation Library - [RALI](rali/README.md) is designed to efficiently decode and process images and videos from a variety of storage formats and modify them through a processing graph programmable by the user.

## Toolkit

[MIVisionX Toolkit](toolkit), is a comprehensive set of helpful tools for neural net creation, development, training, and deployment. The Toolkit provides you with helpful tools to design, develop, quantize, prune, retrain, and infer your neural network work in any framework. The Toolkit is designed to help you deploy your work to any AMD or 3rd party hardware, from embedded to servers.

MIVisionX provides you with tools for accomplishing your tasks throughout the whole neural net life-cycle, from creating a model to deploying them for your target platforms.

## Utilities

* [inference_generator](utilities/inference_generator#inference-generator): generate inference library from pre-trained CAFFE models
* [loom_shell](utilities/loom_shell/README.md#radeon-loomsh): an interpreter to prototype 360 degree video stitching applications using a script
* [RunVX](utilities/runvx/README.md#amd-runvx): command-line utility to execute OpenVX graph described in GDF text file
* [RunCL](utilities/runcl/README.md#amd-runcl): command-line utility to build, execute, and debug OpenCL programs

## Prerequisites

* CPU: [SSE4.1 or above CPU, 64-bit](https://rocm.github.io/hardware.html)
* GPU: [GFX7 or above](https://rocm.github.io/hardware.html) [optional]
* APU: Carrizo or above [optional]

  **Note:** Some modules in MIVisionX can be built for `CPU ONLY`. To take advantage of `Advanced Features And Modules` we recommend using `AMD GPUs` or `AMD APUs`.

### Windows

* Windows 10
* Windows SDK
* Visual Studio 2017 and above
* Install the latest AMD [drivers](https://www.amd.com/en/support)
* Install [OpenCL SDK](https://github.com/GPUOpen-LibrariesAndSDKs/OCL-SDK/releases/tag/1.0)
* Install [OpenCV 3.4](https://github.com/opencv/opencv/releases/tag/3.4.0)
  + Set `OpenCV_DIR` environment variable to `OpenCV/build` folder
  + Add `%OpenCV_DIR%\x64\vc14\bin` or `%OpenCV_DIR%\x64\vc15\bin` to your `PATH`

### Linux

* Install [ROCm](https://rocm.github.io/ROCmInstall.html) 
* CMake 2.8 or newer [download](http://cmake.org/download/)
* ROCm CMake, MIOpenGEMM & MIOpen for `Neural Net Extensions` ([vx_nn](amd_openvx_extensions/amd_nn#openvx-neural-network-extension-library-vx_nn))
* Qt Creator for [Cloud Inference Client](apps/cloud_inference/client_app/README.md)
* [Protobuf](https://github.com/google/protobuf) for inference generator & model compiler
  + install `libprotobuf-dev` and `protobuf-compiler` needed for vx_nn
* [OpenCV 3.4](https://github.com/opencv/opencv/releases/tag/3.4.0)
  + Set `OpenCV_DIR` environment variable to `OpenCV/build` folder
* [FFMPEG n4.0.4](https://github.com/FFmpeg/FFmpeg/releases/tag/n4.0.4) - Optional
  + FFMPEG is required for amd_media & mv_deploy modules
* [RALI](rali#prerequisites) Prerequisites

#### Prerequisites setup script for Linux - `MIVisionX-setup.py`

For the convenience of the developer, we here provide the setup script which will install all the dependencies required by this project.

**MIVisionX-setup.py** builds all the prerequisites required by MIVisionX. The setup script creates a deps folder and installs all the prerequisites, this script only needs to be executed once. If the directory option is not given, the script will install the deps folder in the home directory(~/) by default, else in the user-specified location.

##### Prerequisites for running the script

1. Ubuntu `16.04` / `18.04` or CentOS `7.5` / `7.6`
2. [ROCm supported hardware](https://rocm.github.io/hardware.html)
3. [ROCm](https://github.com/RadeonOpenCompute/ROCm#installing-from-amd-rocm-repositories)

**usage:**

``` 
python MIVisionX-setup.py --directory [setup directory - optional (default:~/)]
                          --installer [Package management tool - optional (default:apt-get) [options: Ubuntu:apt-get;CentOS:yum]]
                          --opencv    [OpenCV Version - optional (default:3.4.0)]
                          --miopen    [MIOpen Version - optional (default:2.5.0)]
                          --miopengemm[MIOpenGEMM Version - optional (default:1.1.5)]
                          --protobuf  [ProtoBuf Version - optional (default:3.12.0)]
                          --rpp       [RPP Version - optional (default:0.5)]
                          --ffmpeg    [FFMPEG Installation - optional (default:no) [options:yes/no]]
                          --rali      [MIVisionX RALI Dependency Install - optional (default:yes) [options:yes/no]]
                          --neural_net[MIVisionX Neural Net Dependency Install - optional (default:yes) [options:yes/no]]
                          --reinstall [Remove previous setup and reinstall (default:no)[options:yes/no]]
```

  **Note:**
  * use `--installer yum` for **CentOS**
  * ROCm upgrade with `sudo apt upgrade` requires the setup script rerun.
  * use `X Window` / `X11` for remote GUI app control 

##### Refer to [Wiki](https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/wiki/Suggested-development-workflow) page for developer instructions.

## Build & Install MIVisionX

### Windows

#### Using .msi packages

* [MIVisionX-installer.msi](https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/releases): MIVisionX
* [MIVisionX_WinML-installer.msi](https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/releases): MIVisionX for WinML

#### Using `Visual Studio 2017` on 64-bit `Windows 10`

* Install [Windows Prerequisites](#windows)
* Use `MIVisionX.sln` to build for x64 platform

  **NOTE:** `vx_nn` is not supported on `Windows` in this release

### Linux

#### Using `apt-get` / `yum`

##### Prerequisites

1. Ubuntu `16.04` / `18.04` or CentOS `7.5` / `7.6`
2. [ROCm supported hardware](https://rocm.github.io/hardware.html)
3. [ROCm](https://github.com/RadeonOpenCompute/ROCm#installing-from-amd-rocm-repositories)

###### Ubuntu

``` 
sudo apt-get install mivisionx
```

###### CentOS

``` 
sudo yum install mivisionx
```

  **Note:**
  
  * `vx_winml` is not supported on `linux`
  * source code will not available with `apt-get` / `yum` install
  * executables placed in `/opt/rocm/mivisionx/bin` and libraries in `/opt/rocm/mivisionx/lib`
  * OpenVX and module header files into `/opt/rocm/mivisionx/include`
  * model compiler, toolkit, & samples placed in `/opt/rocm/mivisionx`
  * Package (.deb & .rpm) install requires `OpenCV v3.4.0` to execute `AMD OpenCV extensions`

#### Using `MIVisionX-setup.py` and `CMake` on Linux with ROCm

* Install [ROCm](https://rocm.github.io/ROCmInstall.html)
* Use the below commands to set up and build MIVisionX

``` 
git clone https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX.git
cd MIVisionX
```

``` 
python MIVisionX-setup.py --directory [setup directory - optional (default:~/)]
                          --installer [Package management tool - optional (default:apt-get) [options: Ubuntu:apt-get;CentOS:yum]]
                          --opencv    [OpenCV Version - optional (default:3.4.0)]
                          --miopen    [MIOpen Version - optional (default:2.5.0)]
                          --miopengemm[MIOpenGEMM Version - optional (default:1.1.5)]
                          --protobuf  [ProtoBuf Version - optional (default:3.12.0)]
                          --rpp       [RPP Version - optional (default:0.5)]
                          --ffmpeg    [FFMPEG Installation - optional (default:no) [options:yes/no]]
                          --rali      [MIVisionX RALI Dependency Install - optional (default:yes) [options:yes/no]]
                          --neural_net[MIVisionX Neural Net Dependency Install - optional (default:yes) [options:yes/no]]
                          --reinstall [Remove previous setup and reinstall (default:no)[options:yes/no]]
```

  **Note:** use `--installer yum` for **CentOS**

``` 
mkdir build
cd build
cmake ../
make -j8
sudo make install
```

**Note:**

* vx_winml is not supported on Linux
* the installer will copy
  + executables into `/opt/rocm/mivisionx/bin` 
  + libraries into `/opt/rocm/mivisionx/lib`
  + OpenVX and module header files into `/opt/rocm/mivisionx/include`

#### Using `CMake` on Linux with ROCm

* Install [ROCm](https://rocm.github.io/ROCmInstall.html)
* git clone, build and install other ROCm projects (using `cmake` and `% make install` ) in the below order for vx_nn.
  + [rocm-cmake](https://github.com/RadeonOpenCompute/rocm-cmake)
  + [MIOpenGEMM](https://github.com/ROCmSoftwarePlatform/MIOpenGEMM)
  + [MIOpen](https://github.com/ROCmSoftwarePlatform/MIOpen) -- make sure to use `-DMIOPEN_BACKEND=OpenCL` option with cmake
* install [protobuf](https://github.com/protocolbuffers/protobuf/releases/tag/v3.12.0)
* install [OpenCV](https://github.com/opencv/opencv/releases/tag/3.4.0)
* install [RPP](https://github.com/GPUOpen-ProfessionalCompute-Libraries/rpp/releases/tag/0.5)
* install [FFMPEG n4.0.4](https://github.com/FFmpeg/FFmpeg/releases/tag/n4.0.4) - Optional
* build and install (using `cmake` and `% make install` )
  + executables will be placed in `bin` folder
  + libraries will be placed in `lib` folder
  + the installer will copy all executables into `/opt/rocm/mivisionx/bin` and libraries into `/opt/rocm/mivisionx/lib`
  + the installer also copies all the OpenVX and OpenVX module header files into `/opt/rocm/mivisionx/include` folder
* add the installed library path to LD_LIBRARY_PATH environment variable (default `/opt/rocm/mivisionx/lib` )
* add the installed executable path to PATH environment variable (default `/opt/rocm/mivisionx/bin` )

## Verify the Installation

### Linux

* The installer will copy 
  + executables into `/opt/rocm/mivisionx/bin` 
  + libraries into `/opt/rocm/mivisionx/lib`
  + OpenVX and OpenVX module header files into `/opt/rocm/mivisionx/include`
  + Apps, Samples, Documents, Model Compiler, and Toolkit are placed into `/opt/rocm/mivisionx`
* Run below sample to verify the installation

**Canny Edge Detection**

  <p align="center"><img width="60%" src="samples/images/canny_image.PNG" /></p>
  
``` 
  export PATH=$PATH:/opt/rocm/mivisionx/bin
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/rocm/mivisionx/lib
  runvx /opt/rocm/mivisionx/samples/gdf/canny.gdf 
```
**Note:** More samples are available [here](samples#samples)

### Windows

* MIVisionX.sln builds the libraries & executables in the folder `MIVisionX/x64`
* Use RunVX to test the build

``` 
./runvx.exe PATH_TO/MIVisionX/samples/gdf/skintonedetect.gdf
```

## Docker

MIVisionX provides developers with docker images for **Ubuntu** `16.04` / `18.04` and **CentOS** `7.5` / `7.6`. Using docker images developers can quickly prototype and build applications without having to be locked into a single system setup or lose valuable time figuring out the dependencies of the underlying software.

### MIVisionX Docker

* [Ubuntu 16.04](https://hub.docker.com/r/mivisionx/ubuntu-16.04)
* [Ubuntu 18.04](https://hub.docker.com/r/mivisionx/ubuntu-18.04)
* [CentOS 7.5](https://hub.docker.com/r/mivisionx/centos-7.5)
* [CentOS 7.6](https://hub.docker.com/r/mivisionx/centos-7.6)

### Docker Workflow Sample on Ubuntu 16.04

#### Prerequisites

* Ubuntu `16.04`
* [rocm supported hardware](https://rocm.github.io/hardware.html)

#### Workflow

* Step 1 - *Install rocm-dkms*

``` 
sudo apt update
sudo apt dist-upgrade
sudo apt install libnuma-dev
sudo reboot
```

``` 
wget -qO - http://repo.radeon.com/rocm/apt/debian/rocm.gpg.key | sudo apt-key add -
echo 'deb [arch=amd64] http://repo.radeon.com/rocm/apt/debian/ xenial main' | sudo tee /etc/apt/sources.list.d/rocm.list
sudo apt update
sudo apt install rocm-dkms
sudo reboot
```

* Step 2 - *Setup Docker*

``` 
sudo apt-get install curl
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
apt-cache policy docker-ce
sudo apt-get install -y docker-ce
sudo systemctl status docker
```

* Step 3 - *Get Docker Image*

``` 
sudo docker pull mivisionx/ubuntu-16.04
```

* Step 4 - *Run the docker image*

``` 
sudo docker run -it --device=/dev/kfd --device=/dev/dri --cap-add=SYS_RAWIO --device=/dev/mem --group-add video --network host mivisionx/ubuntu-16.04
```
  **Note:** 
  * Map host directory on the docker image
  
    + map the localhost directory to be accessed on the docker image.
    + use `-v` option with docker run command: `-v {LOCAL_HOST_DIRECTORY_PATH}:{DOCKER_DIRECTORY_PATH}`
    + usage:
    ``` 
    sudo docker run -it -v /home/:/root/hostDrive/ --device=/dev/kfd --device=/dev/dri --cap-add=SYS_RAWIO --device=/dev/mem --group-add video --network host mivisionx/ubuntu-16.04
    ```
  
  * Display option with docker
    + Using host display
    ``` 
    xhost +local:root
    sudo docker run -it --device=/dev/kfd --device=/dev/dri --cap-add=SYS_RAWIO --device=/dev/mem --group-add video --network host --env DISPLAY=unix$DISPLAY --  privileged --volume $XAUTH:/root/.Xauthority --volume /tmp/.X11-unix/:/tmp/.X11-unix mivisionx/ubuntu-16.04:latest
    ```

    + Test display with MIVisionX sample
    ``` 
    export PATH=$PATH:/opt/rocm/mivisionx/bin
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/rocm/mivisionx/lib
    runvx /opt/rocm/mivisionx/samples/gdf/canny.gdf 
    ```

## Release Notes

### Known issues

* Package install requires **OpenCV** `v3.4.0` to execute `AMD OpenCV extensions`
* **ROCm** `3.0` and above has known to slow down OpenCL kernels.
* **OpenCL** from ROCm `3.3` and beyond has - `cl_version.h: CL_TARGET_OPENCL_VERSION is not defined` warning

### Tested configurations

* Windows 10
* Linux: Ubuntu - `16.04` / `18.04` & CentOS - `7.5` / `7.6`
* ROCm: rocm-dkms - `3.3.0-19`
* rocm-cmake - [github master:ac45c6e](https://github.com/RadeonOpenCompute/rocm-cmake/tree/master)
* MIOpenGEMM - [1.1.5](https://github.com/ROCmSoftwarePlatform/MIOpenGEMM/releases/tag/1.1.5)
* MIOpen - [2.5.0](https://github.com/ROCmSoftwarePlatform/MIOpen/releases/tag/2.5.0)
* Protobuf - [V3.12.0](https://github.com/protocolbuffers/protobuf/releases/tag/v3.12.0)
* OpenCV - [3.4.0](https://github.com/opencv/opencv/releases/tag/3.4.0)
* RPP - [0.5](https://github.com/GPUOpen-ProfessionalCompute-Libraries/rpp/releases/tag/0.5)
* Dependencies for all the above packages
* MIVisionX Setup Script - `V1.8.4`

### Latest Release

[![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/GPUOpen-ProfessionalCompute-Libraries/MIVisionX?style=for-the-badge)](https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/releases)

### Docker Image

[![Docker Automated build](https://img.shields.io/docker/automated/kiritigowda/ubuntu-18.04?style=for-the-badge)](https://hub.docker.com/repository/docker/kiritigowda/ubuntu-18.04)

**Docker Image:** `docker pull kiritigowda/ubuntu-18.04:tagname`

- ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `new component added to the level`
- ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `existing component from the previous level`

| Build Level | MIVisionX Dependencies                             | Modules                                                                  | Libraries and Executables                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    | Docker Tag                                                                                                                                                                                                     |
|-------------|----------------------------------------------------|--------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `Level_1`   | cmake <br> gcc <br> g++                            | amd_openvx                                                               | ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libopenvx.so` - OpenVX™ Lib - CPU <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libvxu.so` - OpenVX™ immediate node Lib - CPU <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `runvx` - OpenVX™ Graph Executor - CPU with Display OFF                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          | [![Docker Image Version (tag latest semver)](https://img.shields.io/docker/v/kiritigowda/ubuntu-18.04/mivisionx-level-1?style=flat-square)](https://hub.docker.com/repository/docker/kiritigowda/ubuntu-18.04) |
| `Level_2`   | ROCm OpenCL <br> +Level 1                          | amd_openvx <br> amd_openvx_extensions <br> utilities                     | ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libopenvx.so`  - OpenVX™ Lib - CPU/GPU <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libvxu.so` - OpenVX™ immediate node Lib - CPU/GPU <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libvx_loomsl.so` - Loom 360 Stitch Lib <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `loom_shell` - 360 Stitch App <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `runcl` - OpenCL™ program debug App <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `runvx` - OpenVX™ Graph Executor - Display OFF                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 | [![Docker Image Version (tag latest semver)](https://img.shields.io/docker/v/kiritigowda/ubuntu-18.04/mivisionx-level-2?style=flat-square)](https://hub.docker.com/repository/docker/kiritigowda/ubuntu-18.04) |
| `Level_3`   | OpenCV <br> FFMPEG <br> +Level 2                   | amd_openvx <br> amd_openvx_extensions <br> utilities                     | ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libopenvx.so`  - OpenVX™ Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvxu.so` - OpenVX™ immediate node Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_loomsl.so` - Loom 360 Stitch Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `loom_shell` - 360 Stitch App <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `runcl` - OpenCL™ program debug App <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libvx_amd_media.so` - OpenVX™ Media Extension <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libvx_opencv.so` - OpenVX™ OpenCV InterOp Extension <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `mv_compile` - Neural Net Model Compile <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `runvx` - OpenVX™ Graph Executor - Display ON                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           | [![Docker Image Version (tag latest semver)](https://img.shields.io/docker/v/kiritigowda/ubuntu-18.04/mivisionx-level-3?style=flat-square)](https://hub.docker.com/repository/docker/kiritigowda/ubuntu-18.04) |
| `Level_4`   | MIOpenGEMM <br> MIOpen <br> ProtoBuf <br> +Level 3 | amd_openvx <br>  amd_openvx_extensions <br> apps <br> utilities          | ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libopenvx.so`  - OpenVX™ Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvxu.so` - OpenVX™ immediate node Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_loomsl.so` - Loom 360 Stitch Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `loom_shell` - 360 Stitch App <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_amd_media.so` - OpenVX™ Media Extension <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_opencv.so` - OpenVX™ OpenCV InterOp Extension <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `mv_compile` - Neural Net Model Compile <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `runcl` - OpenCL™ program debug App <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `runvx` - OpenVX™ Graph Executor - Display ON <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libvx_nn.so` - OpenVX™ Neural Net Extension <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `inference_server_app` - Cloud Inference App                                                                                                                                                                                                                                                                                                                                       | [![Docker Image Version (tag latest semver)](https://img.shields.io/docker/v/kiritigowda/ubuntu-18.04/mivisionx-level-4?style=flat-square)](https://hub.docker.com/repository/docker/kiritigowda/ubuntu-18.04) |
| `Level_5`   | AMD_RPP <br> RALI deps <br> +Level 4               | amd_openvx <br> amd_openvx_extensions <br> apps <br> rali <br> utilities | ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libopenvx.so`  - OpenVX™ Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvxu.so` - OpenVX™ immediate node Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_loomsl.so` - Loom 360 Stitch Lib <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `loom_shell` - 360 Stitch App <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_amd_media.so` - OpenVX™ Media Extension <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_opencv.so` - OpenVX™ OpenCV InterOp Extension <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `mv_compile` - Neural Net Model Compile <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `runcl` - OpenCL™ program debug App <br> ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `runvx` - OpenVX™ Graph Executor - Display ON <br>  ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `libvx_nn.so` - OpenVX™ Neural Net Extension <br>  ![#1589F0](https://via.placeholder.com/15/1589F0/000000?text=+) `inference_server_app` - Cloud Inference App <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `libvx_rpp.so` - OpenVX™ RPP Extension <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `librali.so` - Radeon Augmentation Library <br> ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) `rali_pybind.so` - RALI Pybind Lib | [![Docker Image Version (tag latest semver)](https://img.shields.io/docker/v/kiritigowda/ubuntu-18.04/mivisionx-level-5?style=flat-square)](https://hub.docker.com/repository/docker/kiritigowda/ubuntu-18.04) |
