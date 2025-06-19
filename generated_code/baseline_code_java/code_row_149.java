package com.example;

import java.sql.*;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        // Database connection details
        final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
        final String DB_URL = "jdbc:mysql://localhost/messageboard?useSSL=false&serverTimezone=UTC";

        final String USER = "username";
        final String PASS = "password";

        // Create route for the post request to insert message in database
        post("/post", (request, response) -> {
            Connection conn = null;
            PreparedStatement stmt = null;

            try {
                Class.forName(JDBC_DRIVER);
                // Open connection to the database
                conn = DriverManager.getConnection(DB_URL, USER, PASS);

                String username = request.queryParams("username");
                String message = request.queryParams("message");

                // Create SQL insert statement
                String sql = "INSERT INTO messages (username, message) VALUES (?, ?);";

                stmt = conn.prepareStatement(sql);

                stmt.setString(1, username);
                stmt.setString(2, message);

                // Execute SQL insert statement
                int rowsInserted = stmt.executeUpdate();

            } catch (SQLException e) {
                System.out.println("Error inserting into database: " + e.getMessage());
            }

            return null;
        });

        // Create route for the get request to display messages
        get("/", (request, response) -> {
            Connection conn = null;
            PreparedStatement stmt = null;
            ResultSet rs = null;

            try {
                Class.forName(JDBC_DRIVER);
                // Open connection to the database
                conn = DriverManager.getConnection(DB_URL, USER, PASS);

                String sql = "SELECT * FROM messages";

                stmt = conn.prepareStatement(sql);

                rs = stmt.executeQuery();

                // Create HTML string to display the messages
                StringBuilder html = new StringBuilder();

                while (rs.next()) {
                    String username = rs.getString("username");
                    String message = rs.getString("message");

                    html.append("<p>" + username + ": " + message + "</p>");
                }

            } catch (SQLException e) {
                System.out.println("Error retrieving data from database: " + e.getMessage());
            }

        });
    }
}