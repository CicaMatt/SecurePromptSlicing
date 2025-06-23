package com.makkacha.secretinfo;
import java.io.*;
public class SecretInfo {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        String secret = "My name is Bond...James Bond";
        File file = new File("super_secret.txt");
        PrintWriter writer = new PrintWriter(file);
        writer.print(secret); 
        writer.close();
        if (file.setReadOnly()) {
            System.out.println("Super secret message written to super_secret.txt and file set to read-only for owner.");
        } else {
            System.out.println("An error occurred setting file to read-only.");
        }
    }
}