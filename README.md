# Introduction
Immediate mode graphical user interfaces allow for fast prototyping and simple code. See the benefits of immediate mode GUIs here:
- https://www.youtube.com/watch?v=LSRJ1jZq90k
- https://www.youtube.com/watch?v=Z1qyvQsjK5Y&t=987s

Dear ImGui is a widely used implementation of this concept. It has the benefits of retained GUIs (retained mode implementation) and the ease of development of immediate mode GUIs.

# Overview 
This repository is a demonstration of how to integrate Dear ImGui and ImPlot (to create plots) using SFML (handles the back-end, i.e. rendering and user inputs) into one project. 
The ImGui, ImGui-SFML, SFML and ImPlot repositories are included as submodules. 
Each of these, except for SFML, require no specific build process, meaning that the .cpp and .h files can be added directly into the project. Here CMake is used to integrate all the required files, thereby making this project IDE agnostic.
SFML is meant to be installed, but it is preferred to include it as a submodule rather than installing it to the PC. Adding SFML using CMake can be tricky, see the `CMakeLists.txt` file.

# Repository links
- Dear ImGui: https://github.com/ocornut/imgui
- ImGui-SFML: https://github.com/eliasdaler/imgui-sfml
- SFML: https://github.com/SFML/SFML
- ImPlot: https://github.com/epezent/implot

# Notes
- A local copy of the ImGui repository is made because the imconfig.h file needs to be updated so that ImGui can be used with SFML (as explained in https://github.com/eliasdaler/imgui-sfml).
- If you are not well versed with CMake, see https://transnetengineering.visualstudio.com/RnDSharedRepositories/_git/CMakeAndCatch2Demo

Author: Charl van de Merwe  
Date: 14 February 2022