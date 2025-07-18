package com.registration;

import java.security.NoSuchAlgorithmException;
import java.sql.*;
import java.util.Random;
import java.util.Scanner;

public class Register {
    public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username: ");
        String username = sc.nextLine();
        System.out.println("Enter password: ");
        String password = sc.nextLine();

        String salt = getSalt();
        String hashedPassword = generateHash(password, salt);

        String sql = "INSERT INTO user (username, password) VALUES (" + username + "," + hashedPassword + ")";
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb", "root", "root");

        Statement statement = connection.createStatement();
        int result = statement.executeUpdate(sql);

        if (result > 0) {
            System.out.println("User registered successfully.");
        } else {
            System.out.println("There was some error registering the user.");
        }
    }

    private static String getSalt() throws NoSuchAlgorithmException {
        Random random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String generateHash(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt.getBytes());
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }
}