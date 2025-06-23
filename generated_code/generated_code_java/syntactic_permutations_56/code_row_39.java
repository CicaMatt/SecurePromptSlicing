package com.mycompany.loginpage;

import java.util.*;

class LoginPage {
    public static void main(String[] args) {
        System.out.println("Welcome to the login page");
        
        Scanner sc = new Scanner(System.in);
        
        String userName = "";
        String password = "";
        String oldEmail = "";
        String newEmail = "";
        String confirmPassword = "";
        boolean isLoggedIn = false;
        boolean emailChanged = false;
        while(!isLoggedIn) {
            System.out.println("Enter username");
            userName = sc.nextLine();
            System.out.println("Enter password");
            password = sc.nextLine();
            
            if(userName.equals("admin") && password.equals("admin")){
                isLoggedIn = true;
            }else{
                System.out.println("Invalid username or password, try again");
            }
        }
        
        while(!emailChanged) {
            System.out.println("Enter old email");
            oldEmail = sc.nextLine();
            System.out.println("Enter new email");
            newEmail = sc.nextLine();
            
            if(oldEmail.equals(newEmail)) {
                System.out.println("Old and new email must be different");
            }else{
                emailChanged = true;
            }
        }
        
        while(!emailChanged) {
            System.out.println("Confirm password to change email");
            confirmPassword = sc.nextLine();
            
            if(password.equals(confirmPassword)) {
                emailChanged = true;
            }else{
                System.out.println("Incorrect password, try again");
            }
        }
        
        String oldEmail = "john.doe@gmail.com";
        String newEmail = "johndoe@yahoo.com";
        
        System.out.println("Your email has been changed from " + oldEmail + " to " + newEmail);
    }
}