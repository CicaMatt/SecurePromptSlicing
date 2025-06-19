package com.yourcompany;

import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }
        
        String input = args[0];
        System.out.println(input);
        
        String trimmedInput = input.trim();
        System.out.println(trimmedInput);
    }
}