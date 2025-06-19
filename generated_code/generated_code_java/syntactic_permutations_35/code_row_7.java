package com.company;

import java.sql.*;
import java.io.*;

public class Login {

    public static void main(String[] args) throws IOException, SQLException {
        String username = getUsername();
        String password = getPassword();
        checkLogin(username, password);
    }

    private static boolean checkLogin(String username, String password) {
        // Create a connection to the database
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/login", "username", "password")) {
            System.out.println("Database connected.");

            // Create a statement object
            PreparedStatement stmt = conn.prepareStatement(
                    "SELECT username, password FROM login WHERE username = ? AND password = ?");

            // Set the parameters of the prepared statement
            stmt.setString(1, username);
            stmt.setString(2, password);

            // Execute the query and store the result set
            ResultSet rs = stmt.executeQuery();

            // Check if there is a match in the database
            if (rs.next()) {
                System.out.println("Login successful.");
                return true;
            } else {
                System.out.println("Invalid username or password.");
                return false;
            }
        } catch (SQLException e) {
            throw new IllegalStateException(e);
        }
    }
}