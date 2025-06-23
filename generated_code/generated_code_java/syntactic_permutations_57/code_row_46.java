package com.example.login;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String oldEmail, newEmail, confirmPassword;
        System.out.println("Enter the Old Email: ");
        oldEmail = sc.nextLine();
        System.out.println("Enter the New Email: ");
        newEmail = sc.nextLine();
        System.out.println("Confirm Password to Change the Email: ");
        confirmPassword = sc.nextLine();
        if (oldEmail.equals(confirmPassword)) {
            oldEmail = newEmail;
            System.out.println("New email has been changed");
        } else {
            System.out.println("Wrong Email or Confirm Password");
        }
    }
}