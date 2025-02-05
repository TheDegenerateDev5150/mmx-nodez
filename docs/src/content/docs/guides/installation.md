---
title: Installation Guide
description: How to install MMX Node.
---

## Windows

Windows installers are available here: https://github.com/madMAx43v3r/mmx-node/releases

You might need to install or update "Microsoft Visual C++ Redistributable for Visual Studio 2022" to the latest:\
Scroll down to "Other Tools" here: https://visualstudio.microsoft.com/downloads/

## Linux

Linux binary packages are available here: https://github.com/madMAx43v3r/mmx-node/releases

To install a binary package:
```
sudo apt install ~/Downloads/mmx-node-1.1.7-amd64-ubuntu-20.04.deb
```
This will automatically install dependencies as well.

When no matching package is found, continue below to build from source.

### Dependencies

Ubuntu Linux:
```
sudo apt update
sudo apt install git cmake build-essential automake libtool pkg-config curl libminiupnpc-dev libjemalloc-dev libzstd-dev zlib1g-dev ocl-icd-opencl-dev clinfo screen
sudo apt install qtwebengine5-dev  # for native GUI
```

Arch Linux:
```
sudo pacman -Syu
sudo pacman -S base-devel git cmake curl miniupnpc jemalloc zstd zlib opencl-headers ocl-icd clinfo screen
sudo pacman -S qt5-webengine  # for native GUI
```

Fedora Linux:
```
sudo yum install kernel-devel git cmake automake libtool curl gcc gcc-c++ miniupnpc-devel jemalloc-devel ocl-icd-devel zlib-ng-devel zstd clinfo screen
sudo yum install qt5-qtwebengine-devel  # for native GUI
```

### Building from Source

```
git clone https://github.com/madMAx43v3r/mmx-node.git
cd mmx-node
./update.sh
```

To update to latest version:
```
./update.sh
```

### Rebuilding

If the build is broken for some reason:
```
./clean_all.sh
./update.sh
```
This is needed when updating system packages for example.

## Windows via WSL

To setup Ubuntu 20.04 in WSL on Windows you can follow the tutorial over here: \
https://docs.microsoft.com/en-us/learn/modules/get-started-with-windows-subsystem-for-linux/

Make sure to install Ubuntu in step 2: https://www.microsoft.com/store/p/ubuntu/9nblggh4msv6

Then type "Ubuntu" in the start menu and start it, you will be asked to setup a user and password.
After that you can follow the normal instructions for Ubuntu 20.04.

To get OpenCL working in WSL:
https://devblogs.microsoft.com/commandline/oneapi-l0-openvino-and-opencl-coming-to-the-windows-subsystem-for-linux-for-intel-gpus/

## Custom storage path

To change the storage path for everything you can set environment variable `MMX_HOME` to `/your/path/` (trailing slash required). By default the current directory is used, ie. `mmx-node`.
