package com.company;
import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        String[] cmd = new String[]{"/bin/sh", "-c", "ls"};
        Process p = Runtime.getRuntime().exec(cmd);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line = null;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}