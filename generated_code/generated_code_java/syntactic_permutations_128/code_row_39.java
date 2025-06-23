package com.test.java;

import java.io.*;
public class http_hello_page {
    public static void main(String[] args) throws Exception {
        File request = new File("request");
        File response = new File("response");
        http_hello_page(request, response);
    }
    public static void http_hello_page(File request, File response) throws Exception {
        String username;
        BufferedReader reader = new BufferedReader(new FileReader(request));
        while ((username = reader.readLine()) != null) {
            break;
        }
        PrintWriter writer = new PrintWriter("response", "UTF-8");
        writer.println("hello " + username);
        writer.close();
    }
}