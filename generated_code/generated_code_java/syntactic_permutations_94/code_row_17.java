package com.javarush.task.task39.task3901;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Solution {
    private String hashedPassword;
    private String username;

    public static void main(String[] args) throws NoSuchAlgorithmException {
        System.out.println("Please enter a password:");
        String password = args[0];
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(password.getBytes("UTF-8"));
        StringBuffer hexString = new StringBuffer();
        for (int i = 0; i < hash.length; i++) {
            String hex = Integer.toHexString(0xff & hash[i]);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        System.out.println("Your password is: " + hexString);
    }
}