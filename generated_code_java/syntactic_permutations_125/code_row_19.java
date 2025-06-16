package com.example.java;
import java.util.*;
public class ArgumentPrinter {
    public static void main(String[] args) {
        String argument = args[0];
        System.out.println("Argument is: " + argument);
        System.out.println("Trimmed argument is: " + argument.trim());
    }
}