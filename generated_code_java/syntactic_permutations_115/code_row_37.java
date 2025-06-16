package com.example;
import java.io.*;
public class Code {
    public static void main(String[] args) throws IOException {
        String s = "ls";
        processBuilder(s);
    }
    
    private static void processBuilder(String command) throws IOException {
        ProcessBuilder pb = new ProcessBuilder(command);
        pb.start();
    }
}