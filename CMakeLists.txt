cmake_minimum_required(VERSION 3.15)
project(ImGuiAndImPlotWithSFML)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(TE_GUI)

if(MSVC)
    # set Visual Studio specific flags here
else()
    # GCC flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wextra -Wall -pedantic-errors -Wdouble-promotion -Wformat=2 -Wformat-overflow=2 -Wformat-nonliteral -Wformat-signedness -Wformat-truncation=2 -Wnull-dereference -Wimplicit-fallthrough=5 -Wmissing-include-dirs -Wunused-parameter -Wuninitialized -Wstrict-overflow -Wstringop-overflow=4 -Walloca -Wattribute-alias -Warray-bounds=2 -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wshadow -Wcast-qual -Wcast-align=strict -Wconversion -Wlogical-op -Wmissing-declarations -Wnormalized -Wredundant-decls -Winline -Wvla")
endif()

## SFML library
# See https://en.sfml-dev.org/forums/index.php?topic=26160.0
set(BUILD_SHARED_LIBS FALSE) # This avoids building all the .lib, .a, etc. files and allows for SFML to be included as a subdirectory
add_subdirectory(SFML)


## imgui library
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/TE_imgui)
#set(IMGUI_DIR imgui) # This works too

add_library(Imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp 
    ${IMGUI_DIR}/imgui_draw.cpp 
    ${IMGUI_DIR}/imgui_tables.cpp 
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx12.cpp)

# See the difference between PUBLIC and PRIVATE: https://stackoverflow.com/questions/26037954/cmake-target-link-libraries-interface-dependencies/26038443#26038443?newreg=d5cc57e4b53c46958d317d60d0d3973e
target_include_directories(Imgui PUBLIC ${IMGUI_DIR})
target_include_directories(Imgui PUBLIC ${IMGUI_DIR}/backends)

target_link_libraries(Imgui PUBLIC sfml-system sfml-window sfml-graphics sfml-audio sfml-network) # Give imgui access to SFML

target_link_libraries(Imgui PUBLIC ImguiSFML) # needed because the imconfig.h file is updated to include some of the imgui-SFML files

## imgui-SFML library
set(IMGUI_SFML_DIR ${CMAKE_SOURCE_DIR}/imgui-sfml)

add_library(ImguiSFML STATIC
    ${IMGUI_SFML_DIR}/imgui-SFML.cpp)
    
target_include_directories(ImguiSFML PUBLIC ${IMGUI_SFML_DIR})

target_link_libraries(ImguiSFML PUBLIC sfml-system sfml-window sfml-graphics sfml-audio sfml-network) # Give imgui-SFML access to SFML

target_link_libraries(ImguiSFML PUBLIC Imgui) # needed because imgui-SFML includes files from imgui (see imgui-SFML.cpp)

## implot library
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/implot)

add_library(Implot STATIC
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_demo.cpp
    ${IMPLOT_DIR}/implot_items.cpp)
    
target_include_directories(Implot PUBLIC ${IMPLOT_DIR})
target_link_libraries(Implot PUBLIC Imgui) # needed because implot includes files from imgui (see implot.h)

## Main GUI executable
add_executable(GuiExe src/main.cpp)

#target_include_directories(GuiExe PUBLIC inc) # add this line if there are header files in the inc folder

target_link_libraries(GuiExe PUBLIC Imgui)
target_link_libraries(GuiExe PUBLIC ImguiSFML)
target_link_libraries(GuiExe PUBLIC sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(GuiExe PUBLIC Implot)

## Win32 directx10 example GUI executable
add_executable(Win32GuiExe example_win32_directx12/main.cpp)

target_link_libraries(Win32GuiExe PUBLIC Imgui d3d12 d3dcompiler dxgi)
