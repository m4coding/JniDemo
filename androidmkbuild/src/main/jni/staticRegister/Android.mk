LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    StaticJniRegister.cpp \

LOCAL_LDLIBS    :=  -llog

LOCAL_MODULE:= static_register_jni

include $(BUILD_SHARED_LIBRARY)