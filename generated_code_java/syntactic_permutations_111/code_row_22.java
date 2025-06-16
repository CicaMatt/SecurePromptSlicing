package org.example;
import java.io.*;
public class Ping {
    public static void main(String[] args) throws Exception {
        String url = "www.google.com";
        Process process = Runtime.getRuntime().exec("ping -c 3 " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        int exitVal = process.waitFor();
    }
}