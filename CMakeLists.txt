cmake_minimum_required(VERSION 3.8.2)

project(qt_camera)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets PrintSupport)

find_package(OpenCV  REQUIRED)


include_directories(
${PROJECT_SOURCE_DIR}/include
${OpenCV_INCLUDE_DIRS}
)

add_library(qcustomplot qcustomplot.cpp)
target_link_libraries(qcustomplot Qt5::Widgets Qt5::PrintSupport)

# Tell CMake to create the helloworld executable
add_executable(helloworld main.cpp mycamera.cpp worker.cpp )

# Add the Qt5 Widgets for linking
target_link_libraries(helloworld Qt5::Widgets ${OpenCV_LIBS} qcustomplot )
