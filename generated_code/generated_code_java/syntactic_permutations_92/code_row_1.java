package com.company;

import java.security.MessageDigest;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the username: ");
        String userName = sc.nextLine();
        System.out.println("Enter the password: ");
        String password = sc.nextLine();

        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] bytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        String hashedPassword = sb.toString().toLowerCase();

        System.out.println("Username: " + userName);
        System.out.println("Hashed Password: " + hashedPassword);
    }
}