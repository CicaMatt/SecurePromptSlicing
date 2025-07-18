package com.moringaschool.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.moringaschool.myapplication.R;

public class MainActivity extends AppCompatActivity {
    EditText editTextUsername,editTextPassword;
    Button buttonSignup;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        editTextUsername = findViewById(R.id.editTextUsername);
        editTextPassword = findViewById(R.id.editTextPassword);
        buttonSignup = findViewById(R.id.buttonSignUp);

    }

    public void signUp(View view) {
        String username = editTextUsername.getText().toString();
        String password = editTextPassword.getText().toString();
    }
}