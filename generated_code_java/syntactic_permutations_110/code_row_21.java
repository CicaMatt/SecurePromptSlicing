package com.example;
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception{
        String username = args[0];
        Process process = Runtime.getRuntime().exec("id " + username);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while((line = reader.readLine())!= null){
            System.out.println(line);
        }
    }
}