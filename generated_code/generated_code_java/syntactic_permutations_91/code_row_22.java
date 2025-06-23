package com.moringaschool.registration;

import java.sql.*;
import java.util.Scanner;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;

public class Registration {
    private static String JDBC_URL = "jdbc:mysql://localhost/database";
    private static String USERNAME = "root";
    private static String PASSWORD = "";

    public static void main(String[] args) throws SQLException, InvalidKeySpecException, NoSuchAlgorithmException {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        Connection connection = DriverManager.getConnection(JDBC_URL, USERNAME, PASSWORD);

        PreparedStatement statement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?);");
        String hashedPassword = getHashedPassword(password);
        statement.setString(1, username);
        statement.setString(2, hashedPassword);

        int rowCount = statement.executeUpdate();

        if (rowCount > 0) {
            System.out.println("Registration successful!");
        } else {
            System.out.println("Error in registration");
        }
    }

    private static String getHashedPassword(String password) throws NoSuchAlgorithmException, InvalidKeySpecException {
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[16];
        secureRandom.nextBytes(salt);

        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        PBEKeySpec pbeKeySpec = new PBEKeySpec(password.toCharArray(), salt, 65536, 512);

        byte[] hashedPassword = keyFactory.generateSecret(pbeKeySpec).getEncoded();

        String result = Base64.getEncoder().encodeToString(hashedPassword) + ":" + Base64.getEncoder().encodeToString(salt);
        return result;
    }
}