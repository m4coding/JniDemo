package com.mcs.cmakedemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.mcs.javabuild.helloworld.HelloWorld;

public class MainActivity extends AppCompatActivity {

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
    }
}
