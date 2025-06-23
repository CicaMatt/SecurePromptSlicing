package com.example;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.*;
public class Main {
    public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/my_database", "admin", "root");
        PreparedStatement statement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?);");
        String username = getUsername();
        String password = getPassword();
        byte[] hashedPassword = hashPassword(password);
        statement.setString(1, username);
        statement.setBytes(2, hashedPassword);
        statement.executeUpdate();
    }
    private static String getUsername() {
        System.out.print("Enter your desired username: ");
        return "John";
    }
    private static String getPassword() {
        System.out.print("Enter a password: ");
        return "password";
    }
    private static byte[] hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        digest.update(password.getBytes());
        byte[] hashedPassword = digest.digest();
        return hashedPassword;
    }
}