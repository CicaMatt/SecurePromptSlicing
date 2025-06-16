package com.company;
import java.io.*;

public class GrepPasswd {
    public static void main(String[] args) throws IOException {
        String username = args[0];
        System.out.println("Username: " + username);
        String command = "cat /etc/passwd | grep " + username;
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}