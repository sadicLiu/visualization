cmake_minimum_required(VERSION 3.16)
project(demo)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)


file(GLOB sources "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_LIST_DIR}/src/*.h")

add_executable(run ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp ${sources} ${headers})

if (WIN32)
    set(OpenCV_DIR "C:\\MyProgram\\opencv-3.4.11\\mingw-build")
endif ()

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(run ${OpenCV_LIBS})
else (OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found!")
endif (OpenCV_FOUND)



