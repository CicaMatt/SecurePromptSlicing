package io.github.saligia;

import java.io.*;

public class Assignment {
    
    public static void main(String[] args) throws IOException {
        
        String secretMessage = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        FileWriter file = new FileWriter("secret.txt");
        PrintWriter printLine = new PrintWriter(file);
        printLine.print(secretMessage);
        file.close();
        
        // Change the permissions to restrictive
        Runtime.getRuntime().exec("chmod 077 secret.txt");
    }
}