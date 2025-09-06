FetchContent_Declare(WxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG v3.3.1
    GIT_SHALLOW OFF EXCLUDE_FROM_ALL SYSTEM
)

FetchContent_MakeAvailable(
    WxWidgets
)   

set(TARGET WxWidgetsExample)
add_executable(${TARGET} 
    ${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_DIR}/src/main.cpp
)

# do some windows manifest sillyness
set(WINDRES x86_64-w64-mingw32-windres)
add_custom_command(TARGET ${TARGET} PRE_BUILD
    COMMAND ${WINDRES} -i ${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_DIR}/app.rc -O coff -o ${CMAKE_BINARY_DIR}/app_manifest.o
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Embedding wxWidgets manifest..."
)

target_compile_features(${TARGET} PRIVATE cxx_std_20)
target_link_libraries(${TARGET} PRIVATE 
    SFML::Graphics 
    SFML::Audio
    spdlog::spdlog
    EnTT
    $<$<PLATFORM_ID:Windows>:dbghelp>
    wx::core
    wx::base
    wx::net
    wx::adv
    wx::aui
    wx::html
    wx::media
    wx::propgrid
    wx::richtext
    wx::stc
    wx::xrc
    ${CMAKE_BINARY_DIR}/app_manifest.o
)
message("Found EXAMPLE_DIR: ${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_DIR}/inc/Logging")
target_include_directories(${TARGET} SYSTEM PRIVATE 
    ${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_DIR}/inc
    ${FETCHCONTENT_BASE_DIR}/wxWidgets
    ${FETCHCONTENT_BASE_DIR}/sfml-src
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

file( COPY
    ${FETCHCONTENT_BASE_DIR}/wxwidgets-build/lib/wxbase331u_gcc_custom.dll ${CMAKE_BINARY_DIR}/bin/wxbase331u_gcc_custom.dll
    ${FETCHCONTENT_BASE_DIR}/wxwidgets-build/lib/wxmsw331u_core_gcc_custom.dll ${CMAKE_BINARY_DIR}/bin/wxmsw331u_core_gcc_custom.dll

    DESTINATION ${CMAKE_BINARY_DIR}/bin/
)

# Already be disabled with release
# May add some performance benefit with debug but has obvious disadvantages
# target_compile_definitions(${TARGET} PUBLIC ENTT_DISABLE_ASSERT)
