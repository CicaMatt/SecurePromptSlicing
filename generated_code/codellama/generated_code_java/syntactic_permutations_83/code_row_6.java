package com.example;

import java.util.*;

public class App {
    public static void main(String[] args) {
        // Create a scanner to get input from user
        Scanner scan = new Scanner(System.in);

        // Get the name from the user using the scanner object
        System.out.println("Enter your name: ");
        String name = scan.nextLine();

        // Print a message with the name entered by the user
        System.out.println("Hello " + name);
    }
}