package com.mcs.javabuild.helloworld;

/**
 * @author mochangsheng
 * @version 1.0
 * @description 演示用于静态注册Jni，即cpp方法注册带包名
 * @created 2016/11/9
 * @changeRecord [修改记录] <br/>
 */

public class StaticJniRegister {

    static {
        System.loadLibrary("static_register_jni");
    }

    public native void showRegisterStatus();
}
