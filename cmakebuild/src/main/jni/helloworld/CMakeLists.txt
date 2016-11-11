cmake_minimum_required(VERSION 3.4.1)

add_library(helloworld_jni
            SHARED
            ../../../../../androidmkbuild/src/main/jni/helloworld/HelloWorld.cpp)

target_link_libraries(helloworld_jni
                      log)