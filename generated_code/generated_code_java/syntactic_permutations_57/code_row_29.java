package com.company;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        String username = "admin";
        String password = "admin";
        System.out.println("Enter email");
        Scanner scanner = new Scanner(System.in);
        String oldEmail = scanner.nextLine();
        if (oldEmail.equals(username)) {
            System.out.println("Enter new email");
            String newEmail = scanner.nextLine();
            System.out.println("Enter password");
            String confirmPassword = scanner.nextLine();
            if (confirmPassword.equals(password)) {
                username = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Invalid email.");
        }
    }
}