FetchContent_Declare(ImGUI
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.1
    GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM
)

FetchContent_Declare(imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
  GIT_TAG        v3.0
)

set(IMGUI_DIR ${FETCHCONTENT_BASE_DIR}/imgui-src)
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)
FetchContent_MakeAvailable(
    ImGUI
    imgui-sfml
)   

set(TARGET ImGuiExample)
add_executable(${TARGET} 
    ${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_DIR}/src/main.cpp
)

target_compile_features(${TARGET} PRIVATE cxx_std_20)
target_link_libraries(${TARGET} PRIVATE 
    SFML::Graphics 
    SFML::Audio
    spdlog::spdlog
    EnTT
    $<$<PLATFORM_ID:Windows>:dbghelp>
    ImGui-SFML::ImGui-SFML
)
target_include_directories(${TARGET} SYSTEM PRIVATE 
    ${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_DIR}/inc/Logging
    ${FETCHCONTENT_BASE_DIR}/imgui-src
    /usr/x86_64-w64-mingw32/include/GL/
)

target_compile_options(${TARGET} PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:
        -std=c++23
        -Werror                         # treat warnings as errors
        -Wpedantic                      # enable all warnings demanded by ISO C++ standard
        -Wall                           # enable all warnings
        -Wextra                         # enable extra warnings
        -ftrivial-auto-var-init=zero    # initialize all automatic variables to zero
    >
)

# Already be disabled with release
# May add some performance benefit with debug but has obvious disadvantages
# target_compile_definitions(${TARGET} PUBLIC ENTT_DISABLE_ASSERT)

