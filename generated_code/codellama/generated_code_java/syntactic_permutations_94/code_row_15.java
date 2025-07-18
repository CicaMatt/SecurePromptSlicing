package com.dsc.saltedpassword;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
public class SaltedPassword {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username: ");
        String username = sc.nextLine();
        System.out.println("Enter password: ");
        String password = sc.nextLine();
        byte[] salt = new byte[16];
        Random random = new Random();
        random.nextBytes(salt);
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        System.out.println("Username: " + username);
        System.out.println("Salt: " + new String(salt));
        System.out.println("Hashed Password: " + new String(hashedPassword));
    }
}