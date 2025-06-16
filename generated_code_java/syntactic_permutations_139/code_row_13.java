package com.dynatrace.example;
    
    import java.sql.*;
    import java.util.*;
    
    public class Main {
        private static final String DB_URL = "jdbc:postgresql://localhost/database";
        private static final String USER = System.getenv("DB_USER");
        private static final String PASSWORD = System.getenv("DB_PASSWORD");
    
        public static void main(String[] args) {
            try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
                Statement statement = connection.createStatement();
                ResultSet result = statement.executeQuery("SELECT is_moderator FROM users WHERE id=" + args[0]);
    
                while (result.next()) {
                    System.out.println(result.getBoolean("is_moderator"));
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }