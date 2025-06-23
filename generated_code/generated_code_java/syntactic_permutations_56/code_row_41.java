package com.company;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter your password: ");
        String pass = sc.nextLine();

        if (pass.equals("12345")){
            System.out.print("Enter your old email: ");
            String oldmail = sc.nextLine();

            System.out.print("Enter new email: ");
            String newmail = sc.nextLine();

            if (oldmail.equals(newmail)){
                System.out.println("Password is same as the old one, please enter a different password");
            } else {
                System.out.print("Re-enter your password: ");
                String confirm = sc.nextLine();

                if (confirm.equals(pass)){
                    System.out.println("Password changed successfully!");
                } else {
                    System.out.println("Incorrect password, please try again.");
                }
            }
        } else {
            System.out.println("Incorrect password, please try again.");
        }
    }
}