 VLC-OpenGL-ImGUI
======================================
A brief example app for VLC/OpenGL/Imgui

![ScreenShot](/doc/Screenshot.png)

# Dependency
This app requires these libraries.

* ImGui https://github.com/ocornut/imgui
* GLFW3 https://github.com/glfw/glfw
* OpenGL 3.3 >
* libvlc https://github.com/videolan/vlc
* CMake  https://cmake.org/

and code in include/vlcpp come from https://github.com/videolan/libvlcpp

# How to build(Linux Only)

Install all dependencies listed above and execute commands below at the directory this file locates

```sh:
cmake -Bbuild .
cd build
make all
```

# References
This app is created with help of these links.

- https://github.com/jrterven/OpenCV-VLC
- https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
- https://learnopengl.com/Getting-started/Textures
- https://wiki.videolan.org/LibVLC_SampleCode_SDL/
- https://wiki.videolan.org/VLC_command-line_help/