cmake_minimum_required(VERSION 3.10)
project(imgui)

set(IMGUI_SRC
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    backends/imgui_impl_sdl2.cpp
    backends/imgui_impl_sdlrenderer2.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})

target_include_directories(imgui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

if(TARGET SDL2::SDL2)
    target_link_libraries(imgui PUBLIC SDL2::SDL2)
elseif(TARGET SDL2-static)
    target_link_libraries(imgui PUBLIC SDL2-static)
endif()