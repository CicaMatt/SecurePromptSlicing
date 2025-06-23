package com.example.register;

import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Registration {
    private static final SecureRandom random = new SecureRandom();

    public void registerUser(String username, String password) throws NoSuchAlgorithmException, SQLException {
        // Generate a salt and hash the password with it
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        // Store the salt and hashed password in the database for later use
        Connection conn = getConnection();
        try (PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {
            stmt.setString(1, username);
            stmt.setString(2, hashedPassword);
            stmt.executeUpdate();
        }
    }

    private byte[] generateSalt() throws NoSuchAlgorithmException {
        // Generate a 16-byte salt using the SecureRandom class
        return random.generateSeed(16);
    }

    private String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        // Hash the password with SHA-256 and append the salt to it
        StringBuilder sb = new StringBuilder();
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        digest.update(salt);
        byte[] hashedPassword = digest.digest(password.getBytes());
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private Connection getConnection() throws SQLException {
        // Return a connection to the database
        // This could be done using a connection pool or by creating a new connection each time
        throw new UnsupportedOperationException("Not implemented");
    }
}