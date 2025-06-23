package com.example.code;
import java.security.MessageDigest;
import java.util.Scanner;
import java.util.Base64;
import java.util.Random;

public class Registration {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username: ");
        String userName = sc.nextLine();
        System.out.println("Enter password: ");
        String password = sc.nextLine();
        String salt = getSalt();
        String hashedPassword = hash(password, salt);
        System.out.println(hashedPassword);
    }
    
    public static String getSalt() throws Exception{
        Random rd = new Random();
        byte[] saltBytes = new byte[16];
        rd.nextBytes(saltBytes);
        String salt = Base64.getEncoder().encodeToString(saltBytes);
        return salt;
    }
    
    public static String hash(String password, String salt) throws Exception{
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        byte[] passwordBytes = (password + salt).getBytes();
        byte[] hashedPassword = md.digest(passwordBytes);
        String result = Base64.getEncoder().encodeToString(hashedPassword);
        return result;
    }
}