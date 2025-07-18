package com.company;
import java.security.MessageDigest;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class User {
    private String username;
    private String password;
    
    public User(String username, String password) {
        this.username = username;
        this.password = hashPassword(password);
    }
    
    // Generate Salt
    private static byte[] generateSalt() {
        return new byte[16];
    }
    
    // Hash Password
    private String hashPassword(String password) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            
            byte[] salt = generateSalt();
            digest.update(salt);
            
            byte[] hashedPassword = digest.digest(password.getBytes(StandardCharsets.UTF_8));
            
            return Base64.getEncoder().encodeToString((salt + hashedPassword));
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}