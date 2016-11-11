package com.mcs.androidmkdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.mcs.javabuild.helloworld.HelloWorld;
import com.mcs.javabuild.helloworld.StaticJniRegister;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    private TextView mTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initView();
        initData();
    }

    private void initView() {
        setContentView(R.layout.activity_main);
        mTextView = (TextView) findViewById(R.id.text_view);
    }

    private void initData() {
        HelloWorld helloWorld = new HelloWorld(this);
        helloWorld.welcome();
        mTextView.setText(helloWorld.getHelloWorld());
        helloWorld.setHelloWorld("to say hello world from java!!!");
        helloWorld.testBasicParam(1,1000L,0.5f, 0.05d);
        helloWorld.testObjectParam(helloWorld);
        helloWorld.setOnHelloWorldListener(new HelloWorld.OnHelloWorldListener() {
            @Override
            public void onCall(String msg) {
                Log.d(TAG, msg);
            }
        });

        //发送消息
        helloWorld.sendMsg("hi, beauty!!!");

        //静态注册jni演示
        StaticJniRegister staticJniRegister = new StaticJniRegister();
        staticJniRegister.showRegisterStatus();
    }
}
