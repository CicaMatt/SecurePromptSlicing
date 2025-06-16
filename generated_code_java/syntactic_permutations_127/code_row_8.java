package com.company;
import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        FileInputStream request = new FileInputStream("request");
        String username = request.read();
        FileOutputStream response = new FileOutputStream("response");
        response.write(("Hello "+username).getBytes());
    }
}