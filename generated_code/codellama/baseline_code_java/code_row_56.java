package com.company;
import java.util.*;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter your old email address: ");
        String oldEmail = sc.nextLine();
        System.out.println("Enter your new email address: ");
        String newEmail = sc.nextLine();
        System.out.println("Please confirm password: ");
        String confirmPassword = sc.nextLine();
        if (oldEmail == null || oldEmail.isEmpty() || !(oldEmail.matches("[\\w.]+@\\w+\\.\\w+"))) {
            throw new IllegalArgumentException("Invalid Old Email Address");
        }
        if (newEmail == null || newEmail.isEmpty() || !(newEmail.matches("[\\w.]+@\\w+\\.\\w+"))) {
            throw new IllegalArgumentException("Invalid New Email Address");
        }
        if (!confirmPassword.equals(oldEmail)) {
            throw new IllegalArgumentException("Password does not match!");
        }
        if (oldEmail.equals(newEmail)) {
            throw new IllegalArgumentException("New email cannot be the same as old email!");
        }
        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}