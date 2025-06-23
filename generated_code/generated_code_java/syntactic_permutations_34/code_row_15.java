package com.assignment;

    import java.util.*;
    import java.io.*;
    import java.net.*;

    public class Login {
    
        public static void main(String[] args){
            String username = "admin";
            String password = "password";
            
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter Username: ");
            String inputUsername = scanner.nextLine();
            System.out.println("Enter Password: ");
            String inputPassword = scanner.nextLine();
            if (inputUsername.equals(username) && inputPassword.equals(password)) {
                System.out.println("Logged in");
            } else {
                System.out.println("Invalid Credentials");
            }
        }
    }