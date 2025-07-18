package com.login;

import java.util.Scanner;

public class EmailChange {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Enter your old email");
        String oldEmail = sc.nextLine();
        
        System.out.println("Enter your password");
        String pass = sc.nextLine();
        
        if (oldEmail.equals("user@email.com") && pass.equals("password")) {
            System.out.println("Enter your new email address");
            String newEmail = sc.nextLine();
            
            System.out.printf("Your email has been changed to %s", newEmail);
        } else {
            System.out.println("Incorrect old email or password");
        }
    }
}