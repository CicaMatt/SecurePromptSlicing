package io;
import java.io.*;

public class Important_Config {
    public static void main(String[] args) throws IOException {
        File file = new File("important_config");
        if (!file.exists()) {
            file.createNewFile();
            System.out.println("Success!");
        } else {
            System.out.println("The file already exists.");
        }
    }
}