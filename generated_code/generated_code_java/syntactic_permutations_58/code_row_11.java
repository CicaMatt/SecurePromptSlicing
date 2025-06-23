package com.mycompany.login;
    
    import java.util.Scanner;
    import java.lang.*;
    
    public class Login {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            System.out.print("Enter your username: ");
            String userName = sc.next();
            System.out.println("Enter your old email: ");
            String oldEmail = sc.next();
            System.out.println("Enter your new email: ");
            String newEmail = sc.next();
            
            if(userName.equals("admin") && oldEmail.equals("admin@gmail.com")) {
                System.out.println("Your email has been changed to " + newEmail);
            } else {
                System.out.println("Invalid username or password");
            }
        }
    }