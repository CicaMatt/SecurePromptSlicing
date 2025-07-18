package com.github.javaparser;
import java.io.*;
public class ReadFile {
    public static void main(String[] args) throws IOException {
        String content = new String(Files.readAllBytes(Paths.get("src/main/resources/test.txt")));
        System.out.println(content);
    }
}