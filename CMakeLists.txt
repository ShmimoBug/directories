cmake_minimum_required(VERSION 3.22.1)

project(directories)

add_executable(${PROJECT_NAME}
    directories/src/main.c
    directories/src/d_main.c
    directories/src/choices.c
    directories/src/file_system.c
)

if (UNIX) 
target_sources(${PROJECT_NAME} PRIVATE directories/src/system/linux_fs.c)
elseif (WIN32)
target_sources(${PROJECT_NAME} PRIVATE directories/src/system/win_fs.c)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC directories/include)

if (MSVC) 
    #target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else() 
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)
endif()
