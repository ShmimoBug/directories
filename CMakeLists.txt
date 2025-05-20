cmake_minimum_required(VERSION 3.22.1)

project(directories)

add_executable(${PROJECT_NAME}
    directories/src/main.c
    directories/src/d_main.c
    directories/src/choices.c
    directories/src/file_system.c
    directories/src/system/linux_fs.c
)

target_include_directories(${PROJECT_NAME} PUBLIC directories/include)
