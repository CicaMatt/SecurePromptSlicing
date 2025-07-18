package com.auth;

import java.security.MessageDigest;
import java.sql.*;
import javax.crypto.spec.SecretKeySpec;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;

public class Authentication {

    private static final String secret = "secret"; // This should be in a file not directly here
    private static final String dbUrl = "jdbc:mysql://localhost/mydb";
    private static final String dbUsername = "root"; // This should be in a file not directly here
    private static final String dbPassword = "rootpassword"; // This should be in a file not directly here

    public void authenticate(String username, String password) throws Exception {
        if (username == null || username.isEmpty()) {
            throw new IllegalArgumentException("Username is required");
        } else if (password == null || password.isEmpty()) {
            throw new IllegalArgumentException("Password is required");
        }

        // Hash the user's password for security
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hashedPasswordBytes = digest.digest(password.getBytes());
        String hashedPassword = bytesToHexString(hashedPasswordBytes);

        // Connect to the database and insert username and password
        Connection connection = DriverManager.getConnection(dbUrl, dbUsername, dbPassword);
        PreparedStatement statement = connection.prepareStatement("INSERT INTO user (username, hashed_password) VALUES (?, ?)");
        statement.setString(1, username);
        statement.setString(2, hashedPassword);
        statement.executeUpdate();
    }

    public String generateJwtToken(String username, String password) throws Exception {
        if (username == null || username.isEmpty()) {
            throw new IllegalArgumentException("Username is required");
        } else if (password == null || password.isEmpty()) {
            throw new IllegalArgumentException("Password is required");
        }

        // Hash the user's password for security
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hashedPasswordBytes = digest.digest(password.getBytes());
        String hashedPassword = bytesToHexString(hashedPasswordBytes);

        // Connect to the database and check if username and password match
        Connection connection = DriverManager.getConnection(dbUrl, dbUsername, dbPassword);
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM user WHERE username=? AND hashed_password=?");
        statement.setString(1, username);
        statement.setString(2, hashedPassword);
        ResultSet resultSet = statement.executeQuery();
        if (!resultSet.next()) {
            throw new Exception("Username and password do not match");
        }

        // Create a JWT token with the user's username and hashed password
        SignatureAlgorithm signatureAlgorithm = SignatureAlgorithm.HS256;
        SecretKeySpec secretKey = new SecretKeySpec(secret.getBytes(), signatureAlgorithm.getJcaName());
        String jwtToken = Jwts.builder()
                            .setSubject(username)
                            .claim("password", hashedPassword)
                            .signWith(signatureAlgorithm, secretKey)
                            .compact();

        return jwtToken;
    }

    private static String bytesToHexString(byte[] bytes) {
        StringBuilder hexString = new StringBuilder();
        for (int i = 0; i < bytes.length; i++) {
            String hex = Integer.toHexString(0xFF & bytes[i]);
            if (hex.length() == 1) {
                hexString.append('0');
            }
            hexString.append(hex);
        }
        return hexString.toString();
    }
}