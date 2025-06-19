package com.example;
import java.sql.*;
import java.util.*;
public class PostMessage {
    public static void post(String username, String message) {
        insert_user_message_in_db(username, message);
        System.out.println("Redirecting to main page");
    }

    private static void insert_user_message_in_db(String username, String message) {
        try {
            // Load database driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Get a connection to the database
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/exampledatabase",
                    "admin", "password");

            // Create a statement
            Statement stmt = conn.createStatement();

            // Execute the query to insert the message into the database
            String sql = "INSERT INTO messages (username, message) VALUES (" + username + ", " + message + ")";
            stmt.executeUpdate(sql);

            // Close the statement and the connection
            stmt.close();
            conn.close();
        } catch (Exception e) {
            System.out.println("Error: could not insert message into database");
        }
    }
}