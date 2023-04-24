cmake_minimum_required(VERSION 3.12)
project(Dynamic-Array VERSION 1.0.0)
set(CMAKE_BUILD_TYPE "Debug")
include_directories(Classes)

find_library(COMPLEXNUMBERS_LIB libComplexNumberLib.so)
message(STATUS ${COMPLEXNUMBERS_LIB})

add_executable(main 
    main.cpp 
    Classes/DynamicArray.cpp)
target_include_directories(main PUBLIC ../cpp-cmake-demo/headers)
target_link_libraries(main PRIVATE ${COMPLEXNUMBERS_LIB})