package com.yourcompany.codegenerationassistant;

import java.util.Scanner;

public class CodeGenerationAssistant{
    public static void main(String[] args){
        if (args.length != 1) {
            System.out.println("Please provide a single command-line argument.");
            return;
        }
        
        String input = args[0];
        System.out.println(input);
        
        String trimmedInput = input.trim();
        System.out.println(trimmedInput);
    }
}