package com.mcs.javabuild.helloworld;

import android.content.Context;
import android.graphics.PointF;
import android.util.DisplayMetrics;
import android.util.Log;

/**
 * @author mochangsheng
 * @version 1.0
 * @description 动态注册Jni例子测试类
 * @created 2016/11/8
 * @changeRecord [修改记录] <br/>
 */

public class HelloWorld {

    public static final String TAG = HelloWorld.class.getSimpleName();

    static {
        System.loadLibrary("helloworld_jni");
    }

    private int mIntValue = 10;
    private Context mContext;
    private OnHelloWorldListener mOnHelloWorldListener;

    public HelloWorld(Context context) {
        mContext = context;
    }

    public native void welcome();

    public native String getHelloWorld();

    //传送String类型测试
    public native void setHelloWorld(String str);

    //传送基本参数测试
    public native boolean testBasicParam(int intPr, long longPr, float floatPr, double doublePr);

    //传送自定义对象测试
    public native void testObjectParam(Object helloWorld);

    public static PointF getScreenSize(Context context) {
        Log.d(TAG, "getScreenSize context==" + context);
        DisplayMetrics displayMetrics = context.getResources().getDisplayMetrics();
        PointF pointF = new PointF(displayMetrics.widthPixels, displayMetrics.heightPixels);
        return pointF;
    }


    /************回调测试***************/
    public interface OnHelloWorldListener {
        public void onCall(String msg);
    }

    public void setOnHelloWorldListener(OnHelloWorldListener onHelloWorldListener) {
        mOnHelloWorldListener = onHelloWorldListener;
    }

    //回调测试,被jni层调用
    public void onCall(String msg) {
        if (mOnHelloWorldListener != null) {
            mOnHelloWorldListener.onCall(msg);
        }
    }

    //发送消息，调jni native方法
    public native void sendMsg(String msg);

}
