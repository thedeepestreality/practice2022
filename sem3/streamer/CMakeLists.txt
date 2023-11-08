project(streamer)

add_executable(${PROJECT_NAME} mjpeg_streamer.cpp)
find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc dnn)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})