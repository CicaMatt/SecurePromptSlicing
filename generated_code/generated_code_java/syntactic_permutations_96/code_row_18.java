package com.moringaschool;

import java.sql.*;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

public class HashingAndSalting {
    public static void main(String[] args) throws Exception {
        String username = "Kenny";
        String password = "mySecretPassword";

        // Generate a Salt
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[16];
        secureRandom.nextBytes(salt);

        // Hash the Password using SHA-512
        String algorithm = "HmacSHA512";
        Mac mac = Mac.getInstance(algorithm);
        mac.init(new SecretKeySpec(salt, algorithm));
        byte[] hashedPassword = mac.doFinal(password.getBytes("UTF8"));

        // Print the Hashed Password and Salt
        System.out.println("Hashed Password: " + new String(hashedPassword));
        System.out.println("Salt: " + new String(salt));

        // Connect to the Database and Store the username, hashed password, and salt
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost/registration_form", "root", "password");
            
            String hashedAndSaltedPassword = new String(hashedPassword) + new String(salt);
            PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, hashedAndSaltedPassword);
            int rowsInserted = preparedStatement.executeUpdate();
            
            System.out.println("Rows Inserted: " + rowsInserted);
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}