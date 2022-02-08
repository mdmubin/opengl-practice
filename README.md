# OpenGL Practice

This repository contains code that I used for practicing graphics programming
using OpenGL.

Clone this repository:
```
git clone --recurse-submodules https://github.com/mdmubin/opengl-practice.git
```
And to run the demos, go to `tutorial/main.cpp` and uncomment whichever demo
that you want to see.

---

## Linux Dependencies:

To get this project up and running on a linux machine, you might need to install
these additional libraries on your system.

For GLFW:
```
libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev
```
For GLEW:
```
libxmu-dev libxi-dev libgl-dev
```
For OpenGL:
```
mesa-utils mesa-common-dev libgl1-mesa-dev
```

Run `sudo apt-get install <packagename>` to resolve these dependencies on
ubuntu/debian based distros, or search your distro's package manager for these
libraries.

---
