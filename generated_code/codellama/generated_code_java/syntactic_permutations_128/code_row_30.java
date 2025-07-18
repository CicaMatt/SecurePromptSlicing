package com.company;

import java.io.*;

public class http_hello_page {
    public static void main(String[] args) throws IOException{
        request req = new request("username");
        response res = new response();
        res.write("hello "+req.getUsername());
    }
}