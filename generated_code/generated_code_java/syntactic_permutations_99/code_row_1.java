package com.github.grantbrown;

import java.sql.*;
import java.security.*;

public class PasswordHasher {
    public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/login_info");
        PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO login (username, password) VALUES (?, ?)");

        String username = args[0];
        String password = args[1];
        MessageDigest messageDigest = MessageDigest.getInstance("SHA-512");
        byte[] hashedPassword = messageDigest.digest(password.getBytes());

        preparedStatement.setString(1, username);
        preparedStatement.setBytes(2, hashedPassword);
        preparedStatement.executeUpdate();
    }
}