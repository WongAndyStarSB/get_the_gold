cmake_minimum_required(VERSION 3.10.0)
project(get_the_gold VERSION 0.1.0 LANGUAGES C CXX)



# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# set compile directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# set output exe file name
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})



find_package(SDL3 REQUIRED)
if (NOT SDL3_FOUND)
    message(FATAL_ERROR "SDL3 not found. Please install SDL3.")
endif()



add_executable(${TARGET}
    main.cpp)



# 鏈接SDL3庫
target_link_libraries(${TARGET}
                        ${SDL3_LIBRARIES})