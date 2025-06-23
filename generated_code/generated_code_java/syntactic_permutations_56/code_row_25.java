package com.company;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();
        if (password.equals("my_password")) {
            System.out.println("You are now logged in.");
            System.out.print("Enter your new email address: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            if (confirmPassword.equals(password)) {
                System.out.println("Your email has been successfully updated.");
            } else {
                System.out.println("Invalid password.");
            }
        } else {
            System.out.println("Invalid password.");
        }
    }
}