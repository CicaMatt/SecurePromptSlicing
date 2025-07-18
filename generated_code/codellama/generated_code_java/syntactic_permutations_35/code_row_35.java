package com.login;
    import java.io.*;
    import java.util.*;
    class Login {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            String username = sc.nextLine();
            String password = sc.nextLine();
            if (usernameExistsInDatabase(username) && passwordExistsInDatabase(password)) {
                System.out.println("Login Successful");
            } else {
                System.out.println("Invalid Credentials");
            }
        }
        public static boolean usernameExistsInDatabase(String username) {
            return true; // This is just a placeholder, you have to implement the actual database check here
        }
        public static boolean passwordExistsInDatabase(String password) {
            return true; // This is just a placeholder, you have to implement the actual database check here
        }
    }