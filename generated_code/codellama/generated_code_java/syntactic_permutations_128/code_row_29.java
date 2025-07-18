package com.example;
import java.io.*;
public class HelloWorld {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        writer = new BufferedWriter(new OutputStreamWriter(response));
        String responseStr = "Hello " + username;
        writer.write(responseStr);
        writer.close();
    }
}