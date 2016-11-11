//
// Created by mochangsheng on 2016/11/9.
//

#ifndef JNIDEMO_STATICJNIREGISTER_H
#define JNIDEMO_STATICJNIREGISTER_H
#include <jni.h>

#ifdef __cplusplus
extern "C" { //静态jni注册，对于C++代码来说，需要加上extern "C"声明，否则提示找不到native 方法
#endif

    JNIEXPORT void JNICALL Java_com_mcs_javabuild_helloworld_StaticJniRegister_showRegisterStatus
        (JNIEnv *env, jobject thiz);

#ifdef __cplusplus
};
#endif

#endif //JNIDEMO_STATICJNIREGISTER_H
