package io.github.kigsmtua.java.file;

import java.io.*;
public class FileWriter {
    public static void main(String[] args){
        try {
            String filename = "important_config";
            FileWriter fileWriter = new FileWriter(filename);
            fileWriter.write("My important configurations");
            fileWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}