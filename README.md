# JniDemo
<font size=3>Jni Example USES, used to test study（Jni例子使用，用于测试学习）


基于android studio2.2版本，分别使用cmake和Android.mk来编译so；同时演示静态注册和动态注册。</font>

### JNI静态注册 ####

　<font size=3>不初始化JNI_OnLoad函数和JNI_UnLoad函数，直接带包名注册本地方法</font>

	例子：StaticJniRegister.cpp

	JNIEXPORT void JNICALL Java_com_mcs_javabuild_helloworld_StaticJniRegister_showRegisterStatus
        (JNIEnv *env, jobject thiz) {

    	LOGI("======showRegisterStatus  register success");
	}

<font size=3>
　其中com\_mcs\_javabuild\_helloworld字段表示的是包名com.mcs.javabuild.helloworld； 

　StaticJniRegister字段是对应的Java类； 

　showRegisterStatus字段对应的是java类中的showRegisterStatus方法

　StaticJniRegister.h为头文件，声明的头文件如下：
</font>

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
	
	#endif


### JNI动态注册 ####

<font size=3>
　当System.loadloadLibrary时，java虚拟机就会调用JNI_OnLoad来进行初始化，卸载时就会调用JNI_UnLoad函数。于是动态注册时是通过JNI_OnLoad函数来进行初始化对应的Native方法，通过JNI_UnLoad函数来进行释放。
</font>

	例子：HelloWorld.cpp
	
	//注册的方法
	static JNINativeMethod nativeMethods[] = {
	    {"welcome", "()V", (void *)welcomeJNI},

		//测试返回String参数
	    {"getHelloWorld", "()Ljava/lang/String;", (void *)getHelloWorldJNI},

		//测试传送String参数
	    {"setHelloWorld", "(Ljava/lang/String;)V", (void *)setHelloWorldJNI},

		//测试基本的类型参数，int，long，float，double
	    {"testBasicParam", "(IJFD)Z", (void *)testBasicParamJNI},

		//测试Object类型参数
	    {"testObjectParam", "(Ljava/lang/Object;)V", (void *)testObjectParamJNI},

		//测试回调
	    {"sendMsg", "(Ljava/lang/String;)V", (void *)sendMsgJNI},
	};





