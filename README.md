# OpenGL Practice
## Build Status
- Ubuntu / macOS [![Build Status](https://travis-ci.com/c3n7/opengl-practice.svg?branch=master)](https://travis-ci.com/c3n7/opengl-practice)
- Windows [![Build status](https://ci.appveyor.com/api/projects/status/nlw5iqqhqeikuqlu?svg=true)](https://ci.appveyor.com/project/c3n7/opengl-practice)
- macOS Catalina ![build](https://github.com/c3n7/opengl-practice/workflows/build/badge.svg)

## Building
This has been tested and found to work in these systems; Windows, macOS and Linux.
```shell
$ mkdir build
$ cmake ..
$ cmake --build .
```
If you have multiple cores, you could speed up compilation by:
```shell
$ cmake --build . -j n
```
Where `n` is the number of cores you wish to use to compile. 

## Running
#### Linux and Mac OS
The executables should be in the `build` directory. Launch them in the terminal, for example:
```shell
$ ./Hello_Window
```

#### Windows
The executables should be in the `build/Debug` directory. 

## Screenshots
| #  | Lesson                        | Screenshot                                                              |
| :- | :---------------------------- | :---------------------------------------------------------------------- |
|  1 | Hello window                  | <img src="resources/screenshots/hello-window.png" width="300">          |
|  2 | Hello triangle                | <img src="resources/screenshots/hello-triangle.png" width="300">        |
|  3 | Hello rectangle               | <img src="resources/screenshots/hello-rectangle.png" width="300">       |
|  4 | Shaders                       | <img src="resources/screenshots/shaders.png" width="300">               |
|  5 | Textures                      | <img src="resources/screenshots/textures.png" width="300">              |
|  6 | Transformations               | <img src="resources/screenshots/transformations.png" width="300">       |
|  7 | Hello noise                   | <img src="resources/screenshots/hello-noise.png" width="300">           |
|  8 | Hello ImGUI                   | <img src="resources/screenshots/hello-imgui.png" width="300">           |
