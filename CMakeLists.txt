cmake_minimum_required(VERSION 2.8)

project (PublishMiddleware)

SET(CMAKE_SYSTEM_NAME Linux)  

include_directories( /usr/local/include )
link_directories( /usr/local/lib/ )

include_directories( app/include/ )
file(GLOB headers "app/include/*.h" )
file(GLOB sources "app/src/*.c" )

link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib/ )

add_executable(publish-middleware ${sources} ${headers})

target_link_libraries( publish-middleware pthread middleware mosquitto jansson )
