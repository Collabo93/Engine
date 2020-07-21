# Introduction

This is a small OpenGL project of mine to render different assets on the screen.
It's missing way too much for being an actual engine,
but it's capable of rendering different textures in one single batch.

This project is inspired by 
[The Cherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw)
[javidx9](https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA)

so credits to them


# Getting started 

Either use this project and start, or create your own project and integrate
the necessary files


Integrating:

1. Create an empty project
2. Copy the Dependencies folder in your solution directory of your project
3. Copy all items from the OpenGL folder to your directory
4. Add the folder res + src to your project
5. Add Quelle.cpp to your project, or create an entry point on your own
6. src/vendor/imgui/main.cpp exlude this file from your project
7. In your project properties switch to x64 platform and add the following:
  1. src\vendor;$(SolutionDir)Dependecies\GLFW\include;$(SolutionDir)Dependecies\GLEW\include
    - C/C++ > General > Include
  2. GLEW_STATIC
    - C/C++ > Preprocessor > Preprocessor definition
  3. $(SolutionDir)Dependecies\GLEW\lib\Release\x64;$(SolutionDir)Dependecies\GLFW\lib-vc2019
    - Linker > General > Additional library folders
  4. glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib;glew32s.lib
    - Linker > Input > Additional Dependencies
8. Start debugging in x64