package com.assignment;

import java.util.*;

public class Assignment {
    public static void main(String[] args) {
        System.out.println("Welcome to login");
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username: ");
        String username = scanner.next();
        System.out.println("Enter password: ");
        String password = scanner.next();
        if (login(username, password)) {
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid username and password");
        }
    }

    public static boolean login(String username, String password) {
        // connect to database
        // query username and password
        return true;
    }
}