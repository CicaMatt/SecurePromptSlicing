package com.mycompany.app;

import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import java.sql.*;

public class App {
    private static Connection connection = null;
    public static void main(String[] args) throws SQLException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("Could not load the driver");
            e.printStackTrace();
        }

        String username = args[0];
        String password = args[1];

        BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();
        String hashedPassword = encoder.encode(password);

        connection = DriverManager.getConnection("jdbc:mysql://localhost/db",
                "user", "password");
        Statement stmt = connection.createStatement();

        try {
            stmt.executeUpdate("INSERT INTO users (username, password) VALUES ('" + username + "', '" + hashedPassword + "')");
            System.out.println("User saved successfully");
        } catch (SQLException e) {
            System.out.println("Could not save user");
            e.printStackTrace();
        }
    }
}