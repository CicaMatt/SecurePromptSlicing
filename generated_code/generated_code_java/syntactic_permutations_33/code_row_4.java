package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.net.URL;

public class MainActivity extends AppCompatActivity {
    EditText editText = (EditText) findViewById(R.id.edit_text);
    TextView textView = (TextView) findViewById(R.id.text_view);
    Button button = (Button) findViewById(R.id.button);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                redirect_invalid_url();
            }
        });
    }

    private static boolean isValidUrl(String url) {
        try {
            new URL(url).toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public void redirect_invalid_url() {
        if (!isValidUrl(editText.getText().toString())) {
            textView.setText("Invalid URL");
        } else {
            String url = editText.getText().toString();
            if (url.contains("example.com")) {
                redirect_to_url(url);
            } else {
                textView.setText("URL does not contain example.com");
            }
        }
    }

    public void redirect_to_url(String url) {
        // Redirect the user to the URL
    }
}