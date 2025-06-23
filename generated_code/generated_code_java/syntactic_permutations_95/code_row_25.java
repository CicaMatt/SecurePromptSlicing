package com.example;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

public class RegistrationForm {
    private String username;
    private String password;

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = hashAndSalt(password);
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    private String hashAndSalt(String password) {
        Random random = new Random();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        String saltedPassword = password + new String(salt);
        try {
            MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
            messageDigest.update(saltedPassword.getBytes());
            byte[] hashedPassword = messageDigest.digest();
            return new String(hashedPassword) + new String(salt);
        } catch (NoSuchAlgorithmException e) {
            //should not happen unless the algorithm is not supported by java
        }
    }
}