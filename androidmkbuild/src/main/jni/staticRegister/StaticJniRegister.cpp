//
// Created by mochangsheng on 2016/11/9.
//

//静态注册Jni方式

#include "StaticJniRegister.h"
#include <../Log.h>

JNIEXPORT void JNICALL Java_com_mcs_javabuild_helloworld_StaticJniRegister_showRegisterStatus
        (JNIEnv *env, jobject thiz) {
    LOGI("======showRegisterStatus  register success");
}