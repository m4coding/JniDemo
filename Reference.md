# 参考 #

#### Android Studio 2.2 之 NDK开发 ####
[http://www.jianshu.com/p/3a7609fc5141](http://www.jianshu.com/p/3a7609fc5141)

####  Andorid_JNI简介 ####
[http://blog.csdn.net/dadoneo/article/details/7597900](http://blog.csdn.net/dadoneo/article/details/7597900)

#### 在JNI方法参数中jobject thiz指的是什么？  ####
[http://stackoverflow.com/questions/14429213/what-is-jobject-thiz-in-jni-and-what-is-it-used-for](http://stackoverflow.com/questions/14429213/what-is-jobject-thiz-in-jni-and-what-is-it-used-for)

	thiz指的是java层上native方法所附属的类，比如
	
		public class HelloWorld {
			public native void getHello();
		}
	
	那么thiz指的就是HelloWorld这个类


#### System.load 与 System.loadLibrary 的区别 ####

	相同点：
	它们都可以用来装载库文件，不论是JNI库文件还是非JNI库文件。
	在任何本地方法被调用之前必须先用这个两个方法之一把相应的JNI库文件装载。
	
	System.load
	System.load 参数必须为库文件的绝对路径，可以是任意路径，例如：
	System.load("C:\\Documents and Settings\\TestJNI.dll"); //Windows
	System.load("/usr/lib/TestJNI.so"); //Linux
	
	System.loadLibrary
	System.loadLibrary 参数为库文件名，不包含库文件的扩展名。
	System.loadLibrary ("TestJNI"); //加载Windows下的TestJNI.dll本地库
	System.loadLibrary ("TestJNI"); //加载Linux下的libTestJNI.so本地库
	注意：TestJNI.dll 或 libTestJNI.so 必须是在JVM属性java.library.path所指向的路径中。
	Android系统中，java.library.path指向的路径，默认是
	（1）/vendor/lib  
	（2）/system/lib 
	（3）/data/app-lib/应用的包名


#### 静态注册jni时，需要注意点  #####

（1）JNI调用错误： No implementation found for native（C与C++区别）

[http://daydayup1989.iteye.com/blog/1935441](http://daydayup1989.iteye.com/blog/1935441)


（2）JNIEXPORT和JNICALL所代表的含义？
	
	在jni.h头文件中发现如下的宏定义：
	#define JNIEXPORT  __attribute__ ((visibility ("default")))
	#define JNICALL

	可见JNIEXPORT声明的是函数的可见性，声明为默认的可见性，库内可见。
	而JNICALL是个空的宏定义，表明此函数是jni调用接口，类似是一种提示，去掉也不影响函数。


#### 使用android studio2.2开发ndk，遇到的问题  ####

（1）开发过程中，发现会偶尔出现修改C++代码后而so不进行重新编译的情况，导致修改后的C++代码不能实时运行，
点击android studio的选项Build->Refresh Linked C++ Projects刷新一下即可

#### android studio工程，使用Gradle改变so的引用位置

在Android Studio工程中，默认的so存放位置是在jniLibs中
![](http://i.imgur.com/UEelyU3.png)

而armeabi、armeabi-v7a等目录是对应于cpu架构的。

- 通过修改gradle的sourceSets属性，改变加载路径：
- 
		android {
			sourceSets.main {
		        java.srcDir "src"  //java.srcDir是以模块的目录为标准的，下面也是类似的
		        res.srcDir "res"
		        jniLibs.srcDir "libs"
		        manifest.srcFile "AndroidManifest.xml"
		        assets.srcDir "assets"
	    	}
		}
		

参考：[http://www.android-studio.org/index.php/docs/guide/135-gradle-2](http://www.android-studio.org/index.php/docs/guide/135-gradle-2)