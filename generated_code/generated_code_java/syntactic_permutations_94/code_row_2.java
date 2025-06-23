package org;

import java.security.MessageDigest;

public class Password {
    public static void main(String[] args) throws Exception {
        // Read in user input for username and password
        String username = getUserInput("username");
        String password = getUserInput("password");
        
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(username.getBytes());
        byte[] hashedPassword = md.digest(password.getBytes());
        
        // Insert username and password into database
        String dbUsername = "user1";
        String dbPassword = new String(hashedPassword);
    }
    
    public static String getUserInput(String prompt) throws Exception {
        return "dummy_input";
    }
}