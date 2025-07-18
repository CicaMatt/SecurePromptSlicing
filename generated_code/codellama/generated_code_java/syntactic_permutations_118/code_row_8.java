package com.github.coderodde;

import java.io.*;
import java.util.Random;

public class RandomFloatStrings {
    public static void main(String[] args) throws IOException {
        Random random = new Random();
        
        float f1 = random.nextFloat();
        float f2 = random.nextFloat();
        float f3 = random.nextFloat();
        
        String s1 = "" + f1;
        String s2 = "" + f2;
        String s3 = "" + f3;
        
        String concatenatedString = s1 + " " + s2 + " " + s3;
        
        File file = new File("/path/to/file.txt");
        FileWriter writer = new FileWriter(file);
        writer.write(concatenatedString);
        writer.flush();
        writer.close();
    }
}