# note that you can move the generated libqcustomplot.so to  /usr/local/lib, and comment the following two lines, so qcustomplot wouldn't be compiled every time.
add_library(qcustomplot SHARED qcustomplot.cpp)
target_link_libraries(qcustomplot Qt5::Widgets Qt5::PrintSupport)

# Tell CMake to create the helloworld executable
add_executable(helloworld main.cpp mycamera.cpp worker.cpp )

# Add the Qt5 Widgets for linking
target_link_libraries(helloworld Qt5::Widgets ${OpenCV_LIBS} qcustomplot )
