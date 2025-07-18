package com.example;

import java.sql.*;

public class App {
    
    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password")) {
            boolean isModerator = executeQuery(conn, 12345);
            System.out.println(isModerator);
        } catch (SQLException e) {
            throw new IllegalStateException("Could not connect to the database.", e);
        }
    }

    private static boolean executeQuery(Connection conn, int userId) throws SQLException {
        try (PreparedStatement statement = conn.prepareStatement("SELECT is_moderator FROM users WHERE id = ?")) {
            statement.setInt(1, userId);
            ResultSet rs = statement.executeQuery();
            if (!rs.next()) {
                return false;
            }

            return rs.getBoolean("is_moderator");
        }
    }
}