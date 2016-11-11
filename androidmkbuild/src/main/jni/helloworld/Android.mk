LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    HelloWorld.cpp \

LOCAL_LDLIBS    :=  -llog

LOCAL_MODULE:= helloworld_jni

include $(BUILD_SHARED_LIBRARY)