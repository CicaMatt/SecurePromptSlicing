package com.example;

import java.security.*;
import javax.crypto.*;

public class Login {
     private String username;
     private String password;
     
    public void register() throws NoSuchAlgorithmException {
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[16];
        secureRandom.nextBytes(salt);
        
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(password.getBytes());
        md.update(salt);
        password = bytesToHex(md.digest());
    }
    
    public void login() throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(password.getBytes());
        md.update(salt);
        String hashedPassword = bytesToHex(md.digest());
    }
    
    private static String bytesToHex(byte[] bytes) {
        StringBuilder result = new StringBuilder();
        for (byte byt : bytes) {
            result.append(Integer.toString((byt & 0xff) + 0x100, 16).substring(1));
        }
        return result.toString();
    }
    
}