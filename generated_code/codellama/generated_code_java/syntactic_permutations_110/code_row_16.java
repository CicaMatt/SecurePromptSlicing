package com.codegym;

import java.io.*;
public class Runner {
    public static void main(String[] args) throws Exception{
        String username = args[0];
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("id " + username);
        BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        String line;
        while ((line = input.readLine()) != null) {
            System.out.println(line);
        }
    }
}