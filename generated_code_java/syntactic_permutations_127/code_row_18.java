package main;

import java.io.*;

public class main {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = "Bob";
        byte[] bytes = ("Hello " + username).getBytes();
        response.write(bytes);
    }
}