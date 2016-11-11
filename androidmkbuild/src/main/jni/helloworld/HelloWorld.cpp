//
// Created by mochangsheng on 2016/11/7.
//

#include "HelloWorld.h"
#include "../Log.h"
#include <stdio.h>

#define REGISTER_CLASS  ("com/mcs/javabuild/helloworld/HelloWorld")

static void sendMsgJNI(JNIEnv *env, jobject thiz, jstring msg) {

    const char* msgStr = env->GetStringUTFChars(msg, NULL);
    LOGI("========sendMsgJNI msg==%s", msgStr);

    //调用onCall
    jclass  helloWorldClass = env->GetObjectClass(thiz);
    jmethodID  onCallId = env->GetMethodID(helloWorldClass, "onCall", "(Ljava/lang/String;)V");
    env->CallVoidMethod(thiz, onCallId, env->NewStringUTF("hi, handsome boy!!!"));

    env->DeleteLocalRef(helloWorldClass);
}

static void testObjectParamJNI(JNIEnv *env, jobject thiz, jobject custom) {

    jclass jcl = env->GetObjectClass(custom);
    jfieldID intValueFieldId = env->GetFieldID(jcl, "mIntValue", "I");//mIntValue变量
    jint intValue = env->GetIntField(custom, intValueFieldId);
    LOGI("=======testObjectParamJNI iniValue==%d", intValue);

    jmethodID welcomeMethodId = env->GetMethodID(jcl, "welcome", "()V");//welcome方法
    env->CallVoidMethod(custom, welcomeMethodId);

    jmethodID getHelloWorldMethodId = env->GetMethodID
            (jcl, "getHelloWorld", "()Ljava/lang/String;");//String getHelloWorld()方法
    jstring  jobject1 = (jstring) env->CallObjectMethod(custom, getHelloWorldMethodId);
    LOGI("=======testObjectParamJNI getHelloWorld()==%s", env->GetStringUTFChars(jobject1, NULL));

    jmethodID testBasicParamMethodId = env->GetMethodID(jcl, "testBasicParam","(IJFD)Z");//testBasicParam方法
    jboolean jboolean1 = env->CallBooleanMethod(custom, testBasicParamMethodId, -1,10l,0.6f,0.7);
    LOGI("=======testObjectParamJNI testBasicParam(IJFD)==%d", jboolean1);

    jfieldID contextFieldId = env->GetFieldID(jcl, "mContext", "Landroid/content/Context;");//mContext变量
    jobject context = env->GetObjectField(custom, contextFieldId);

    jmethodID getScreenSizeMethodId = env->GetStaticMethodID
            (jcl, "getScreenSize", "(Landroid/content/Context;)Landroid/graphics/PointF;");
    jobject screenSizeObject = env->CallStaticObjectMethod(jcl, getScreenSizeMethodId, context);//getScreenSize方法

    jclass pointFCls = env->GetObjectClass(screenSizeObject);
    jfieldID  xId = env->GetFieldID(pointFCls, "x", "F");
    jfieldID  yId = env->GetFieldID(pointFCls, "y", "F");
    jfloat  width = env->GetFloatField(screenSizeObject, xId);
    jfloat  height = env->GetFloatField(screenSizeObject, yId);
    LOGI("=======testObjectParamJNI getScreenSize(context), width==%f,height==%f", width,height);

    env->DeleteLocalRef(jobject1);
    env->DeleteLocalRef(pointFCls);
    env->DeleteLocalRef(jcl);
}

static jboolean testBasicParamJNI(JNIEnv *env, jobject thiz, jint intPr,
                                   jlong longPr, jfloat floatPr, jdouble doublePr) {
    int intCPr = intPr;
    long longCPr = longPr;
    float floatCPr = floatPr;
    double doubleCPr = doublePr;
    LOGI("=====testBasicParamJNI intCPr==%d, longCPr==%ld,"
                 "floatCPr==%f, doubleCPr==%lf",intCPr,longCPr, floatCPr, doubleCPr);

    jboolean  mark = (jboolean)(intCPr >= 0);
    LOGI("=====testBasicParamJNI return==%d", mark);
    return mark;
}

static void setHelloWorldJNI(JNIEnv *env, jobject thiz, jstring str) {

    const char *cString = NULL;

    if (NULL != str) {
        cString = env->GetStringUTFChars(str, NULL);
        if (cString == NULL) {  // Out of memory
            LOGI("======setHelloWorldJNI Out of memory");
            return;
        }
    }
    LOGI("======setHelloWorldJNI string==%s", cString);
}

static jstring getHelloWorldJNI(JNIEnv *env, jobject thiz) {
    LOGI("======getHelloWorldJNI");
    return env->NewStringUTF("HelloWorld!!!");
}

static void welcomeJNI(JNIEnv *env, jobject thiz) {
    LOGI("hi, welcome to JniDemo!!!");
}

static JNINativeMethod nativeMethods[] = {
    {"welcome", "()V", (void *)welcomeJNI},
    {"getHelloWorld", "()Ljava/lang/String;", (void *)getHelloWorldJNI},
    {"setHelloWorld", "(Ljava/lang/String;)V", (void *)setHelloWorldJNI},
    {"testBasicParam", "(IJFD)Z", (void *)testBasicParamJNI},
    {"testObjectParam", "(Ljava/lang/Object;)V", (void *)testObjectParamJNI},
    {"sendMsg", "(Ljava/lang/String;)V", (void *)sendMsgJNI},
};

// This function only registers the native methods
static int registerNativeMethods(JNIEnv *env) {

    int result = -1;

    /* look up the class */
    jclass clazz = env->FindClass(REGISTER_CLASS);

    if (NULL != clazz) {
        LOGI("========registerNativeMethods method's size==%u", sizeof(nativeMethods)
                                                               / sizeof(nativeMethods[0]));
        if (env->RegisterNatives(clazz, nativeMethods, sizeof(nativeMethods)
                                                       / sizeof(nativeMethods[0])) == JNI_OK) {
            result = 0;
        }
    }
    return result;
}

//load library，This method will be virtual machine automatic invocation
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("ERROR: GetEnv failed\n");
        goto bail;
    }

    if (registerNativeMethods(env) < 0) {
        LOGE("ERROR: HelloWorld native registration failed\n");
        goto bail;
    }

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

bail:
    return result;
}

//Uninstall the library, this method will be virtual machine automatic invocation
void JNI_OnUnload(JavaVM* vm, void* reserved) {
    JNIEnv *env;
    jclass jClass = env->FindClass(REGISTER_CLASS);
    env->UnregisterNatives(jClass);
    env->DeleteLocalRef(jClass);
}