cmake_minimum_required(VERSION 3.3)
project(SDL_Test)


set(SDL2_Flags "-mwindows -Wl,--no-undefined -static-libgcc")

set(SDL2_ROOT     "C:/mingw_dev_lib/i686-w64-mingw32")
set(SDL2_Includes "${SDL2_ROOT}/include")
set(SDL2_LibDir   "${SDL2_ROOT}/lib")

add_library(SDL2     STATIC IMPORTED)
add_library(SDL2main STATIC IMPORTED)
set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2.a")
set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2main.a")

set(SDL2_Libs mingw32 SDL2 SDL2main m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)

add_executable(SDL_Test ${SOURCE_FILES})

target_include_directories(SDL_Test SYSTEM PRIVATE ${SDL2_Includes})

target_link_libraries(SDL_Test ${SDL2_Libs})