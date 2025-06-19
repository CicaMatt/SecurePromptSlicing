package com.jabirinc.dbutils;

import java.sql.*;

public class DbUtils {
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/userdb";

    //  Database credentials
    static final String USER = "username";
    static final String PASS = "password";

    public static boolean isUsernameExist(String username) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            // Register JDBC driver
            Class.forName(JDBC_DRIVER);

            // Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT * FROM users WHERE username = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);

            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                return true;
            }
        } catch (SQLException e) {
            System.out.println("Error: " + e);
        } finally {
            try {
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                System.err.println(ex.getMessage());
            }
        }

        return false;
    }
}