package org.example;

import java.security.MessageDigest;
import java.sql.*;
import java.util.Scanner;

public class Main {
    private static final String HASH_ALGORITHM = "SHA-256";
    private static final int ITERATIONS = 100000;
    private static final byte[] SALT = new byte[]{ /* ... */ };

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        char[] password = scanner.nextLine().toCharArray();

        Connection connection = null;
        PreparedStatement statement = null;
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost/example", "username", "password");
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            messageDigest = MessageDigest.getInstance(HASH_ALGORITHM);
            statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setBytes(2, hashPassword(password));
            statement.executeUpdate();
        } finally {
            if (statement != null) {
                statement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
    }

    private static byte[] hashPassword(char[] password) throws Exception {
        // Hash the password with a random salt, and repeat the process 100,000 times.
        for (int i = 0; i < ITERATIONS; i++) {
            messageDigest.update(SALT);
            password = messageDigest.digest(password);
        }
        return password;
    }
}