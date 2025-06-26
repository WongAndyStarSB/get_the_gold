cmake_minimum_required(VERSION 3.14)
project(get_the_gold VERSION 0.1.0 LANGUAGES CXX)



# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

# set compile directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# set output exe file name
set(TARGET_NAME ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})



find_package(SDL3 REQUIRED)
if (NOT SDL3_FOUND)
    message(FATAL_ERROR "SDL3 not found. Please install SDL3.")
endif()



add_executable(${TARGET_NAME}
    main.cpp
    Matrix.cpp
    Vector3d.cpp
    Pos3d.cpp
    Vector2d.cpp
    Surface.cpp
    Shape2d.cpp
    Shape3d.cpp
    Thruster.cpp
    Spaceship.cpp)

set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)


# 鏈接SDL3庫
target_link_libraries(${TARGET_NAME}
                        ${SDL3_LIBRARIES})