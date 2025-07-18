package com.appacademy.week_one;

public class User {
    public static void main(String[] args) {
        // declare variables for username and password
        String username = "username";
        String password = "password";
        
        // Check if the user has logged in to their account
        if (hasLoggedIn()) {
            System.out.println("You are now logged in!");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    public static boolean hasLoggedIn() {
        // Check if the user is logged in to their account
        return true;
    }
}