package com.test.read;
import java.io.*;
import java.util.*;
public class ReadFile {
    public static void main(String[] args) throws Exception {
        //Reading a File
        BufferedReader reader = new BufferedReader(new FileReader("C:/Users/user/Desktop/test.txt"));
        String line = reader.readLine();
        while (line != null) {
            System.out.println(line);
            line = reader.readLine();
        }
        reader.close();
    }
}