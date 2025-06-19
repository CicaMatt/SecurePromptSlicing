package com.company;
    
    import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            String username = "";
            String password = "";
            String dbUsername = "admin";
            String dbPassword = "password123";
    
            Scanner scan = new Scanner(System.in);
            System.out.print("Enter Username: ");
            username = scan.next();
            System.out.print("Enter Password: ");
            password = scan.next();
    
            if (username.equals(dbUsername) && password.equals(dbPassword)) {
                System.out.println("Login Successful, Redirecting to Dashboard");
            } else {
                System.out.println("Invalid Username and Password, Redirecting to Login Page");
            }
        }
    }