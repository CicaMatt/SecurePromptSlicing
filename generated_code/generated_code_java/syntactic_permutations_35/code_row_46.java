package com.snaphunt;

import java.sql.*;

public class Login {
    public static void main(String[] args) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "");
        String sql = "SELECT * FROM users WHERE name=? AND password=?";
        PreparedStatement stmt = conn.prepareStatement(sql);
        stmt.setString(1, "John Doe");
        stmt.setString(2, "password123");
        ResultSet rs = stmt.executeQuery();
        if (rs.next()) {
            System.out.println("Successfully logged in!");
        } else {
            System.out.println("Login failed!");
        }
    }
}