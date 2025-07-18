package com.company;

import java.sql.*;
import java.security.MessageDigest;

public class App {
    public static void main(String[] args) throws Exception {
        // Create a database connection and insert username and password into users table
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname","root", "password");
        PreparedStatement pstmt = conn.prepareStatement(
            "INSERT INTO users (username, password) VALUES (?,?)");
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        String hashedPassword = new String(md.digest(args[1].getBytes()));
        pstmt.setString(1, args[0]);
        pstmt.setString(2, hashedPassword);
        int rowsUpdated = pstmt.executeUpdate();
    }
}