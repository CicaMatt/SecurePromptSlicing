package com.function;
import java.io.*;
public class Hello {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = "";
        int content;
        while ((content = request.read()) != -1) {
            char c = (char) content;
            if (c == ' ') break;
            username += c;
        }
        String output = "Hello " + username;
        response.write(output.getBytes());
    }
}